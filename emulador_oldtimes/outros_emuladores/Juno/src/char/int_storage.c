// $Id: int_storage.c,v 1.1.1.1 2004/09/10 17:26:51 MagicalTux Exp $

#include <string.h>
#include <stdlib.h>

#include "../common/mmo.h"
#include "../common/socket.h"
#include "../common/db.h"
#include "../common/lock.h"
#include "../common/showmsg.h"
#include "char.h"
#include "inter.h"
#include "int_storage.h"
#include "int_pet.h"
#include "int_guild.h"

// ファイル名のデフォルト
// inter_config_read()で再設定される
char storage_txt[1024]="save/storage.txt";
char guild_storage_txt[1024]="save/g_storage.txt";

static struct dbt *storage_db;
static struct dbt *guild_storage_db;

// 倉庫データを文字列に変換
int storage_tostr(char *str,struct storage *p)
{
	int i,j,f=0;
	char *str_p = str;
	str_p += sprintf(str_p,"%d,%d\t",p->account_id,p->storage_amount);

	for(i=0;i<MAX_STORAGE;i++)
		if( (p->storage_[i].nameid) && (p->storage_[i].amount) ){
			str_p += sprintf(str_p,"%d,%d,%d,%d,%d,%d,%d",
				p->storage_[i].id,p->storage_[i].nameid,p->storage_[i].amount,p->storage_[i].equip,
				p->storage_[i].identify,p->storage_[i].refine,p->storage_[i].attribute);
			for(j=0; j<MAX_SLOTS; j++)
				str_p += sprintf(str_p,",%d",p->storage_[i].card[j]);
			str_p += sprintf(str_p," ");
			f++;
		}

	*(str_p++)='\t';

	*str_p='\0';
	if(!f)
		str[0]=0;
	return 0;
}

// 文字列を倉庫データに変換
int storage_fromstr(char *str,struct storage *p)
{
	int tmp_int[256];
	char tmp_str[256];
	int set,next,len,i,j;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		if(sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d%[0-9,-]%n",
		      &tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3],
		      &tmp_int[4], &tmp_int[5], &tmp_int[6], tmp_str, &len) == 8) {
			p->storage_[i].id = tmp_int[0];
			p->storage_[i].nameid = tmp_int[1];
			p->storage_[i].amount = tmp_int[2];
			p->storage_[i].equip = tmp_int[3];
			p->storage_[i].identify = tmp_int[4];
			p->storage_[i].refine = tmp_int[5];
			p->storage_[i].attribute = tmp_int[6];
			
			for(j = 0; j < MAX_SLOTS && tmp_str && sscanf(tmp_str, ",%d%[0-9,-]",&tmp_int[0], tmp_str) > 0; j++)
				p->storage_[i].card[j] = tmp_int[0];
			
			next += len;
			if (str[next] == ' ')
				next++;
		}
		else return 1;
	}
	return 0;
}

int guild_storage_tostr(char *str,struct guild_storage *p)
{
	int i,j,f=0;
	char *str_p = str;
	str_p+=sprintf(str,"%d,%d\t",p->guild_id,p->storage_amount);

	for(i=0;i<MAX_GUILD_STORAGE;i++)
		if( (p->storage_[i].nameid) && (p->storage_[i].amount) ){
			str_p += sprintf(str_p,"%d,%d,%d,%d,%d,%d,%d",
				p->storage_[i].id,p->storage_[i].nameid,p->storage_[i].amount,p->storage_[i].equip,
				p->storage_[i].identify,p->storage_[i].refine,p->storage_[i].attribute);
			for(j=0; j<MAX_SLOTS; j++)
				str_p += sprintf(str_p,",%d",p->storage_[i].card[j]);
			str_p += sprintf(str_p," ");
			f++;
		}

	*(str_p++)='\t';

	*str_p='\0';
	if(!f)
		str[0]=0;
	return 0;
}

int guild_storage_fromstr(char *str,struct guild_storage *p)
{
	int tmp_int[256];
	char tmp_str[256];
	int set,next,len,i,j;

	set=sscanf(str,"%d,%d%n",&tmp_int[0],&tmp_int[1],&next);
	p->storage_amount=tmp_int[1];

	if(set!=2)
		return 1;
	if(str[next]=='\n' || str[next]=='\r')
		return 0;
	next++;
	for(i=0;str[next] && str[next]!='\t';i++){
		if(sscanf(str + next, "%d,%d,%d,%d,%d,%d,%d%[0-9,-]%n",
			&tmp_int[0], &tmp_int[1], &tmp_int[2], &tmp_int[3],
			&tmp_int[4], &tmp_int[5], &tmp_int[6], tmp_str, &len) == 8)
		{
			p->storage_[i].id = tmp_int[0];
			p->storage_[i].nameid = tmp_int[1];
			p->storage_[i].amount = tmp_int[2];
			p->storage_[i].equip = tmp_int[3];
			p->storage_[i].identify = tmp_int[4];
			p->storage_[i].refine = tmp_int[5];
			p->storage_[i].attribute = tmp_int[6];
			for(j = 0; j < MAX_SLOTS && tmp_str && sscanf(tmp_str, ",%d%[0-9,-]",&tmp_int[0], tmp_str) > 0; j++)
				p->storage_[i].card[j] = tmp_int[0];
			next += len;
			if (str[next] == ' ')
				next++;
		}
		else return 1;
	}
	return 0;
}

// アカウントから倉庫データインデックスを得る（新規倉庫追加可能）
struct storage *account2storage(int account_id)
{
	struct storage *s;
	s= (struct storage *) numdb_search(storage_db,account_id);
	if(s == NULL) {
		s = (struct storage *) aCalloc(sizeof(struct storage), 1);
		if(s==NULL){
			ShowFatalError("int_storage: despejo de memoria!\n");
			exit(0);
		}
		memset(s,0,sizeof(struct storage));
		s->account_id=account_id;
		numdb_insert(storage_db,s->account_id,s);
	}
	return s;
}

struct guild_storage *guild2storage(int guild_id)
{
	struct guild_storage *gs = NULL;
	if(inter_guild_search(guild_id) != NULL) {
		gs= (struct guild_storage *) numdb_search(guild_storage_db,guild_id);
		if(gs == NULL) {
			gs = (struct guild_storage *) aCalloc(sizeof(struct guild_storage), 1);
			if(gs==NULL){
				ShowFatalError("int_storage: despejo de memoria!\n");
				exit(0);
			}
//			memset(gs,0,sizeof(struct guild_storage)); aCalloc does this! [Skotlex]
			gs->guild_id=guild_id;
			numdb_insert(guild_storage_db,gs->guild_id,gs);
		}
	}
	return gs;
}

//---------------------------------------------------------
// 倉庫データを読み込む
int inter_storage_init()
{
	char line[65536];
	int c=0,tmp_int;
	struct storage *s;
	struct guild_storage *gs;
	FILE *fp;

	storage_db = numdb_init();

	fp=fopen(storage_txt,"r");
	if(fp==NULL){
		ShowError("impossivel ler : %s\n",storage_txt);
		return 1;
	}
	while(fgets(line,65535,fp)){
		sscanf(line,"%d",&tmp_int);
		s = (struct storage*)aCalloc(sizeof(struct storage), 1);
		if(s==NULL){
			ShowFatalError("int_storage: despejo de memoria!\n");
			exit(0);
		}
//		memset(s,0,sizeof(struct storage)); aCalloc does this...
		s->account_id=tmp_int;
		if(s->account_id > 0 && storage_fromstr(line,s) == 0) {
			numdb_insert(storage_db,s->account_id,s);
		}
		else{
			ShowError("int_storage: data corrompida [%s] linha %d\n",storage_txt,c);
			aFree(s);
		}
		c++;
	}
	fclose(fp);

	c = 0;
	guild_storage_db = numdb_init();

	fp=fopen(guild_storage_txt,"r");
	if(fp==NULL){
		ShowError("impossivel ler : %s\n",guild_storage_txt);
		return 1;
	}
	while(fgets(line,65535,fp)){
		sscanf(line,"%d",&tmp_int);
		gs = (struct guild_storage*)aCalloc(sizeof(struct guild_storage), 1);
		if(gs==NULL){
			ShowFatalError("int_storage: despejo de memoria!\n");
			exit(0);
		}
//		memset(gs,0,sizeof(struct guild_storage)); aCalloc...
		gs->guild_id=tmp_int;
		if(gs->guild_id > 0 && guild_storage_fromstr(line,gs) == 0) {
			numdb_insert(guild_storage_db,gs->guild_id,gs);
		}
		else{
			ShowError("int_storage: data corrompida [%s] linha %d\n",guild_storage_txt,c);
			aFree(gs);
		}
		c++;
	}
	fclose(fp);

	return 0;
}

int storage_db_final (void *k, void *data, va_list ap) {
	struct storage *p = (struct storage *) data;
	if (p) aFree(p);
	return 0;
}
int guild_storage_db_final (void *k, void *data, va_list ap) {
	struct guild_storage *p = (struct guild_storage *) data;
	if (p) aFree(p);
	return 0;
}
void inter_storage_final() {
	numdb_final(storage_db, storage_db_final);
	numdb_final(guild_storage_db, guild_storage_db_final);
	return;
}

int inter_storage_save_sub(void *key,void *data,va_list ap)
{
	char line[65536];
	FILE *fp;
	storage_tostr(line,(struct storage *)data);
	fp=va_arg(ap,FILE *);
	if(*line)
		fprintf(fp,"%s" RETCODE,line);
	return 0;
}
//---------------------------------------------------------
// 倉庫データを書き込む
int inter_storage_save()
{
	FILE *fp;
	int lock;
	if( (fp=lock_fopen(storage_txt,&lock))==NULL ){
		ShowError("int_storage: impossivel escrever [%s] !!! data esta danificada !!!\n",storage_txt);
		return 1;
	}
	numdb_foreach(storage_db,inter_storage_save_sub,fp);
	lock_fclose(fp,storage_txt,&lock);
//	printf("int_storage: %s saved.\n",storage_txt);
	return 0;
}

int inter_guild_storage_save_sub(void *key,void *data,va_list ap)
{
	char line[65536];
	FILE *fp;
	if(inter_guild_search(((struct guild_storage *)data)->guild_id) != NULL) {
		guild_storage_tostr(line,(struct guild_storage *)data);
		fp=va_arg(ap,FILE *);
		if(*line)
			fprintf(fp,"%s" RETCODE,line);
	}
	return 0;
}
//---------------------------------------------------------
// 倉庫データを書き込む
int inter_guild_storage_save()
{
	FILE *fp;
	int  lock;
	if( (fp=lock_fopen(guild_storage_txt,&lock))==NULL ){
		ShowError("int_storage: impossivel ler [%s] !!! data esta perdida !!!\n",guild_storage_txt);
		return 1;
	}
	numdb_foreach(guild_storage_db,inter_guild_storage_save_sub,fp);
	lock_fclose(fp,guild_storage_txt,&lock);
//	printf("int_storage: %s saved.\n",guild_storage_txt);
	return 0;
}

// 倉庫データ削除
int inter_storage_delete(int account_id)
{
	struct storage *s = (struct storage *) numdb_search(storage_db,account_id);
	if(s) {
		int i;
		for(i=0;i<s->storage_amount;i++){
			if(s->storage_[i].card[0] == (short)0xff00)
				inter_pet_delete( MakeDWord(s->storage_[i].card[1],s->storage_[i].card[2]) );
		}
		numdb_erase(storage_db,account_id);
		aFree(s);
	}
	return 0;
}

// ギルド倉庫データ削除
int inter_guild_storage_delete(int guild_id)
{
	struct guild_storage *gs = (struct guild_storage *) numdb_search(guild_storage_db,guild_id);
	if(gs) {
		int i;
		for(i=0;i<gs->storage_amount;i++){
			if(gs->storage_[i].card[0] == (short)0xff00)
				inter_pet_delete( MakeDWord(gs->storage_[i].card[1],gs->storage_[i].card[2]) );
		}
		numdb_erase(guild_storage_db,guild_id);
		aFree(gs);
	}
	return 0;
}

//---------------------------------------------------------
// map serverへの通信

// 倉庫データの送信
int mapif_load_storage(int fd,int account_id)
{
	struct storage *s=account2storage(account_id);
	WFIFOW(fd,0)=0x3810;
	WFIFOW(fd,2)=sizeof(struct storage)+8;
	WFIFOL(fd,4)=account_id;
	memcpy(WFIFOP(fd,8),s,sizeof(struct storage));
	WFIFOSET(fd,WFIFOW(fd,2));
	return 0;
}
// 倉庫データ保存完了送信
int mapif_save_storage_ack(int fd,int account_id)
{
	WFIFOW(fd,0)=0x3811;
	WFIFOL(fd,2)=account_id;
	WFIFOB(fd,6)=0;
	WFIFOSET(fd,7);
	return 0;
}

int mapif_load_guild_storage(int fd,int account_id,int guild_id)
{
	struct guild_storage *gs=guild2storage(guild_id);
	WFIFOW(fd,0)=0x3818;
	if(gs) {
		WFIFOW(fd,2)=sizeof(struct guild_storage)+12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=guild_id;
		memcpy(WFIFOP(fd,12),gs,sizeof(struct guild_storage));
	}
	else {
		WFIFOW(fd,2)=12;
		WFIFOL(fd,4)=account_id;
		WFIFOL(fd,8)=0;
	}
	WFIFOSET(fd,WFIFOW(fd,2));

	return 0;
}
int mapif_save_guild_storage_ack(int fd,int account_id,int guild_id,int fail)
{
	WFIFOW(fd,0)=0x3819;
	WFIFOL(fd,2)=account_id;
	WFIFOL(fd,6)=guild_id;
	WFIFOB(fd,10)=fail;
	WFIFOSET(fd,11);
	return 0;
}

//---------------------------------------------------------
// map serverからの通信

// 倉庫データ要求受信
int mapif_parse_LoadStorage(int fd)
{
	mapif_load_storage(fd,RFIFOL(fd,2));
	return 0;
}
// 倉庫データ受信＆保存
int mapif_parse_SaveStorage(int fd)
{
	struct storage *s;
	int account_id=RFIFOL(fd,4);
	int len=RFIFOW(fd,2);
	if(sizeof(struct storage)!=len-8){
		ShowError("inter storage: erro no tamanho de data %d %d\n",sizeof(struct storage),len-8);
	}
	else {
		s=account2storage(account_id);
		memcpy(s,RFIFOP(fd,8),sizeof(struct storage));
		mapif_save_storage_ack(fd,account_id);
	}
	return 0;
}

int mapif_parse_LoadGuildStorage(int fd)
{
	mapif_load_guild_storage(fd,RFIFOL(fd,2),RFIFOL(fd,6));
	return 0;
}
int mapif_parse_SaveGuildStorage(int fd)
{
	struct guild_storage *gs;
	int guild_id=RFIFOL(fd,8);
	int len=RFIFOW(fd,2);
	if(sizeof(struct guild_storage)!=len-12){
		ShowError("inter storage: erro no tamanho de data %d %d\n",sizeof(struct guild_storage),len-12);
	}
	else {
		gs=guild2storage(guild_id);
		if(gs) {
			memcpy(gs,RFIFOP(fd,12),sizeof(struct guild_storage));
			mapif_save_guild_storage_ack(fd,RFIFOL(fd,4),guild_id,0);
		}
		else
			mapif_save_guild_storage_ack(fd,RFIFOL(fd,4),guild_id,1);
	}
	return 0;
}

// map server からの通信
// ・１パケットのみ解析すること
// ・パケット長データはinter.cにセットしておくこと
// ・パケット長チェックや、RFIFOSKIPは呼び出し元で行われるので行ってはならない
// ・エラーなら0(false)、そうでないなら1(true)をかえさなければならない
int inter_storage_parse_frommap(int fd)
{
	switch(RFIFOW(fd,0)){
	case 0x3010: mapif_parse_LoadStorage(fd); break;
	case 0x3011: mapif_parse_SaveStorage(fd); break;
	case 0x3018: mapif_parse_LoadGuildStorage(fd); break;
	case 0x3019: mapif_parse_SaveGuildStorage(fd); break;
	default:
		return 0;
	}
	return 1;
}
//tradu軋o por Snails (cronus Core Developer)
