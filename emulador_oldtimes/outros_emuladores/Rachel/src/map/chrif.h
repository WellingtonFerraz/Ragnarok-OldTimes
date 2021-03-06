// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _CHRIF_H_
#define _CHRIF_H_

struct auth_node{
	int account_id, login_id1, login_id2, sex, fd;
	time_t connect_until_time; // # of seconds 1/1/1970 (timestamp): Validity limit of the account (0 = unlimited)
	struct map_session_data *sd;	//Data from logged on char.
	struct mmo_charstatus *char_dat;	//Data from char server.
	unsigned int node_created; //For node auto-deleting
};

void chrif_setuserid(char* id);
void chrif_setpasswd(char* pwd);
void chrif_checkdefaultlogin(void);
int chrif_setip(const char* ip);
void chrif_setport(uint16 port);

int chrif_isconnected(void);

extern int chrif_connected;
extern int other_mapserver_count;

void chrif_authreq(struct map_session_data* sd);
void chrif_authok(int fd);
int chrif_scdata_request(int account_id, int char_id);
int chrif_save(struct map_session_data* sd, int flag);
int chrif_charselectreq(struct map_session_data* sd, uint32 s_ip);
void check_fake_id(int fd, struct map_session_data *sd, int target_id);
int chrif_changemapserver(struct map_session_data* sd, short map, int x, int y, uint32 ip, uint16 port);

int chrif_searchcharid(int char_id);
int chrif_changegm(int id,const char *pass,int len);
int chrif_changeemail(int id, const char *actual_email, const char *new_email);
int chrif_char_ask_name(int acc, const char* character_name, unsigned short operation_type, int year, int month, int day, int hour, int minute, int second);
int chrif_reloadGMdb(void);
int chrif_updatefamelist(struct map_session_data *sd);
int chrif_buildfamelist(void);
int chrif_save_scdata(struct map_session_data *sd);
int chrif_ragsrvinfo(int base_rate,int job_rate, int drop_rate);
int chrif_char_offline(struct map_session_data *sd);
int chrif_char_reset_offline(void);
int send_users_tochar(int tid, unsigned int tick, int id, int data);
int chrif_char_online(struct map_session_data *sd);
int chrif_changesex(int id, int sex);
int chrif_chardisconnect(struct map_session_data *sd);
int check_connect_char_server(int tid, unsigned int tick, int id, int data);

int do_final_chrif(void);
int do_init_chrif(void);

int chrif_flush_fifo(void);

#endif /* _CHRIF_H_ */
