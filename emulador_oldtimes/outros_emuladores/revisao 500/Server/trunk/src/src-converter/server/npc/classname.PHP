<?

if ($handle = opendir('./')) {
while (false !== ($file = readdir($handle))) {
if (preg_match("/\.txt$/i",$file)) {
$filecontents = file_get_contents($file);

$filecontents = str_replace('Aprendiz','"+callfunc("classname",0,"S","M")+"',$filecontents);

$filecontents = str_replace('Aprendizes','"+callfunc("classname",0,"P","M")+"',$filecontents);

$filecontents = str_replace('Espadachim','"+callfunc("classname",1,"S","M")+"',$filecontents);

$filecontents = str_replace('Espadachins','"+callfunc("classname",1,"P","M")+"',$filecontents);

$filecontents = str_replace('Mago','"+callfunc("classname",2,"S","M")+"',$filecontents);

$filecontents = str_replace('Maga','"+callfunc("classname",2,"S","F")+"',$filecontents);

$filecontents = str_replace('Magos','"+callfunc("classname",2,"P","F")+"',$filecontents);

$filecontents = str_replace('Magas','"+callfunc("classname",2,"P","F")+"',$filecontents);

$filecontents = str_replace('Arqueiro','"+callfunc("classname",3,"S","M")+"',$filecontents);

$filecontents = str_replace('Arqueira','"+callfunc("classname",3,"S","F")+"',$filecontents);

$filecontents = str_replace('Arqueiros','"+callfunc("classname",3,"P","M")+"',$filecontents);

$filecontents = str_replace('Arqueiras','"+callfunc("classname",3,"P","F")+"',$filecontents);

$filecontents = str_replace('Novi�o','"+callfunc("classname",4,"S","M")+"',$filecontents);

$filecontents = str_replace('Novi�a','"+callfunc("classname",4,"S","F")+"',$filecontents);

$filecontents = str_replace('Novi�os','"+callfunc("classname",4,"P","M")+"',$filecontents);

$filecontents = str_replace('Novi�as','"+callfunc("classname",4,"P","F")+"',$filecontents);

$filecontents = str_replace('Mercador','"+callfunc("classname",5,"S","M")+"',$filecontents);

$filecontents = str_replace('Mercadora','"+callfunc("classname",5,"S","F")+"',$filecontents);

$filecontents = str_replace('Mercadores','"+callfunc("classname",5,"P","M")+"',$filecontents);

$filecontents = str_replace('Mercadoras','"+callfunc("classname",5,"P","F")+"',$filecontents);

$filecontents = str_replace('Gatuno','"+callfunc("classname",6,"S","M")+"',$filecontents);

$filecontents = str_replace('Gatuna','"+callfunc("classname",6,"S","F")+"',$filecontents);

$filecontents = str_replace('Gatunos','"+callfunc("classname",6,"P","M")+"',$filecontents);

$filecontents = str_replace('Gatunas','"+callfunc("classname",6,"P","F")+"',$filecontents);

$filecontents = str_replace('Cavaleiro','"+callfunc("classname",7,"S","M")+"',$filecontents);

$filecontents = str_replace('Cavaleira','"+callfunc("classname",7,"S","F")+"',$filecontents);

$filecontents = str_replace('Cavaleiros','"+callfunc("classname",7,"P","M")+"',$filecontents);

$filecontents = str_replace('Cavaleiras','"+callfunc("classname",7,"P","F")+"',$filecontents);

$filecontents = str_replace('Sacerdote','"+callfunc("classname",8,"S","M")+"',$filecontents);

$filecontents = str_replace('Sacerdotisa','"+callfunc("classname",8,"S","F")+"',$filecontents);

$filecontents = str_replace('Sacerdotes','"+callfunc("classname",8,"P","M")+"',$filecontents);

$filecontents = str_replace('Sacerdotisas','"+callfunc("classname",8,"P","F")+"',$filecontents);

$filecontents = str_replace('Bruxo','"+callfunc("classname",9,"S","M")+"',$filecontents);

$filecontents = str_replace('Bruxa','"+callfunc("classname",9,"S","F")+"',$filecontents);

$filecontents = str_replace('Bruxos','"+callfunc("classname",9,"P","M")+"',$filecontents);

$filecontents = str_replace('Bruxas','"+callfunc("classname",9,"P","F")+"',$filecontents);

$filecontents = str_replace('Ferreiro','"+callfunc("classname",10,"S","M")+"',$filecontents);

$filecontents = str_replace('Ferreira','"+callfunc("classname",10,"S","F")+"',$filecontents);

$filecontents = str_replace('Ferreiros','"+callfunc("classname",10,"P","M")+"',$filecontents);

$filecontents = str_replace('Ferreiras','"+callfunc("classname",10,"P","F")+"',$filecontents);

$filecontents = str_replace('Ca�ador','"+callfunc("classname",11,"S","M")+"',$filecontents);

$filecontents = str_replace('Ca�adora','"+callfunc("classname",11,"S","F")+"',$filecontents);

$filecontents = str_replace('Ca�adores','"+callfunc("classname",11,"P","M")+"',$filecontents);

$filecontents = str_replace('Ca�adoras','"+callfunc("classname",11,"P","F")+"',$filecontents);

$filecontents = str_replace('Mercen�rio','"+callfunc("classname",12,"S","M")+"',$filecontents);

$filecontents = str_replace('Mercen�ria','"+callfunc("classname",12,"S","F")+"',$filecontents);

$filecontents = str_replace('Mercen�rios','"+callfunc("classname",12,"P","M")+"',$filecontents);

$filecontents = str_replace('Mercen�rias','"+callfunc("classname",12,"P","F")+"',$filecontents);

$filecontents = str_replace('Templ�rio','"+callfunc("classname",14,"S","M")+"',$filecontents);

$filecontents = str_replace('Templ�ria','"+callfunc("classname",14,"S","F")+"',$filecontents);

$filecontents = str_replace('Templ�rios','"+callfunc("classname",14,"P","M")+"',$filecontents);

$filecontents = str_replace('Templ�rias','"+callfunc("classname",14,"P","F")+"',$filecontents);

$filecontents = str_replace('Monge','"+callfunc("classname",15,"S","M")+"',$filecontents);

$filecontents = str_replace('Monja','"+callfunc("classname",15,"S","F")+"',$filecontents);

$filecontents = str_replace('Monges','"+callfunc("classname",15,"P","M")+"',$filecontents);

$filecontents = str_replace('Monjas','"+callfunc("classname",15,"P","F")+"',$filecontents);

$filecontents = str_replace('S�bio','"+callfunc("classname",16,"S","M")+"',$filecontents);

$filecontents = str_replace('S�bia','"+callfunc("classname",16,"S","F")+"',$filecontents);

$filecontents = str_replace('S�bios','"+callfunc("classname",16,"P","M")+"',$filecontents);

$filecontents = str_replace('S�bias','"+callfunc("classname",16,"P","F")+"',$filecontents);

$filecontents = str_replace('Arruaceiro','"+callfunc("classname",17,"S","M")+"',$filecontents);

$filecontents = str_replace('Arruaceira','"+callfunc("classname",17,"S","F")+"',$filecontents);

$filecontents = str_replace('Arruaceiros','"+callfunc("classname",17,"P","M")+"',$filecontents);

$filecontents = str_replace('Arruaceiras','"+callfunc("classname",17,"P","F")+"',$filecontents);

$filecontents = str_replace('Alquimista','"+callfunc("classname",18,"S","M")+"',$filecontents);

$filecontents = str_replace('Alquimistas','"+callfunc("classname",18,"P","M")+"',$filecontents);

$filecontents = str_replace('Bardo','"+callfunc("classname",19,"S","M")+"',$filecontents);

$filecontents = str_replace('Odalisca','"+callfunc("classname",19,"S","F")+"',$filecontents);

$filecontents = str_replace('Bardos','"+callfunc("classname",19,"P","M")+"',$filecontents);

$filecontents = str_replace('Odaliscas','"+callfunc("classname",19,"P","F")+"',$filecontents);

$filecontents = str_replace('S. Aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('S. Aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('Super Aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('Super Aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

//===================================================================================================

$filecontents = str_replace('aprendiz','"+callfunc("classname",0,"S","M")+"',$filecontents);

$filecontents = str_replace('aprendizes','"+callfunc("classname",0,"P","M")+"',$filecontents);

$filecontents = str_replace('espadachim','"+callfunc("classname",1,"S","M")+"',$filecontents);

$filecontents = str_replace('espadachins','"+callfunc("classname",1,"P","M")+"',$filecontents);

$filecontents = str_replace('mago','"+callfunc("classname",2,"S","M")+"',$filecontents);

$filecontents = str_replace('maga','"+callfunc("classname",2,"S","F")+"',$filecontents);

$filecontents = str_replace('magos','"+callfunc("classname",2,"P","F")+"',$filecontents);

$filecontents = str_replace('magas','"+callfunc("classname",2,"P","F")+"',$filecontents);

$filecontents = str_replace('arqueiro','"+callfunc("classname",3,"S","M")+"',$filecontents);

$filecontents = str_replace('arqueira','"+callfunc("classname",3,"S","F")+"',$filecontents);

$filecontents = str_replace('arqueiros','"+callfunc("classname",3,"P","M")+"',$filecontents);

$filecontents = str_replace('arqueiras','"+callfunc("classname",3,"P","F")+"',$filecontents);

$filecontents = str_replace('novi�o','"+callfunc("classname",4,"S","M")+"',$filecontents);

$filecontents = str_replace('novi�a','"+callfunc("classname",4,"S","F")+"',$filecontents);

$filecontents = str_replace('novi�os','"+callfunc("classname",4,"P","M")+"',$filecontents);

$filecontents = str_replace('novi�as','"+callfunc("classname",4,"P","F")+"',$filecontents);

$filecontents = str_replace('mercador','"+callfunc("classname",5,"S","M")+"',$filecontents);

$filecontents = str_replace('mercadora','"+callfunc("classname",5,"S","F")+"',$filecontents);

$filecontents = str_replace('mercadores','"+callfunc("classname",5,"P","M")+"',$filecontents);

$filecontents = str_replace('mercadoras','"+callfunc("classname",5,"P","F")+"',$filecontents);

$filecontents = str_replace('gatuno','"+callfunc("classname",6,"S","M")+"',$filecontents);

$filecontents = str_replace('atuna','"+callfunc("classname",6,"S","F")+"',$filecontents);

$filecontents = str_replace('gatunos','"+callfunc("classname",6,"P","M")+"',$filecontents);

$filecontents = str_replace('gatunas','"+callfunc("classname",6,"P","F")+"',$filecontents);

$filecontents = str_replace('cavaleiro','"+callfunc("classname",7,"S","M")+"',$filecontents);

$filecontents = str_replace('cavaleira','"+callfunc("classname",7,"S","F")+"',$filecontents);

$filecontents = str_replace('cavaleiros','"+callfunc("classname",7,"P","M")+"',$filecontents);

$filecontents = str_replace('cavaleiras','"+callfunc("classname",7,"P","F")+"',$filecontents);

$filecontents = str_replace('sacerdote','"+callfunc("classname",8,"S","M")+"',$filecontents);

$filecontents = str_replace('sacerdotisa','"+callfunc("classname",8,"S","F")+"',$filecontents);

$filecontents = str_replace('sacerdotes','"+callfunc("classname",8,"P","M")+"',$filecontents);

$filecontents = str_replace('sacerdotisas','"+callfunc("classname",8,"P","F")+"',$filecontents);

$filecontents = str_replace('bruxo','"+callfunc("classname",9,"S","M")+"',$filecontents);

$filecontents = str_replace('bruxa','"+callfunc("classname",9,"S","F")+"',$filecontents);

$filecontents = str_replace('bruxos','"+callfunc("classname",9,"P","M")+"',$filecontents);

$filecontents = str_replace('bruxas','"+callfunc("classname",9,"P","F")+"',$filecontents);

$filecontents = str_replace('ferreiro','"+callfunc("classname",10,"S","M")+"',$filecontents);

$filecontents = str_replace('ferreira','"+callfunc("classname",10,"S","F")+"',$filecontents);

$filecontents = str_replace('ferreiros','"+callfunc("classname",10,"P","M")+"',$filecontents);

$filecontents = str_replace('ferreiras','"+callfunc("classname",10,"P","F")+"',$filecontents);

$filecontents = str_replace('ca�ador','"+callfunc("classname",11,"S","M")+"',$filecontents);

$filecontents = str_replace('ca�adora','"+callfunc("classname",11,"S","F")+"',$filecontents);

$filecontents = str_replace('ca�adores','"+callfunc("classname",11,"P","M")+"',$filecontents);

$filecontents = str_replace('ca�adoras','"+callfunc("classname",11,"P","F")+"',$filecontents);

$filecontents = str_replace('mercen�rio','"+callfunc("classname",12,"S","M")+"',$filecontents);

$filecontents = str_replace('mercen�ria','"+callfunc("classname",12,"S","F")+"',$filecontents);

$filecontents = str_replace('mercen�rios','"+callfunc("classname",12,"P","M")+"',$filecontents);

$filecontents = str_replace('mercen�rias','"+callfunc("classname",12,"P","F")+"',$filecontents);

$filecontents = str_replace('templ�rio','"+callfunc("classname",14,"S","M")+"',$filecontents);

$filecontents = str_replace('templ�ria','"+callfunc("classname",14,"S","F")+"',$filecontents);

$filecontents = str_replace('templ�rios','"+callfunc("classname",14,"P","M")+"',$filecontents);

$filecontents = str_replace('templ�rias','"+callfunc("classname",14,"P","F")+"',$filecontents);

$filecontents = str_replace('monge','"+callfunc("classname",15,"S","M")+"',$filecontents);

$filecontents = str_replace('monja','"+callfunc("classname",15,"S","F")+"',$filecontents);

$filecontents = str_replace('monges','"+callfunc("classname",15,"P","M")+"',$filecontents);

$filecontents = str_replace('monjas','"+callfunc("classname",15,"P","F")+"',$filecontents);

$filecontents = str_replace('s�bio','"+callfunc("classname",16,"S","M")+"',$filecontents);

$filecontents = str_replace('s�bia','"+callfunc("classname",16,"S","F")+"',$filecontents);

$filecontents = str_replace('s�bios','"+callfunc("classname",16,"P","M")+"',$filecontents);

$filecontents = str_replace('s�bias','"+callfunc("classname",16,"P","F")+"',$filecontents);

$filecontents = str_replace('arruaceiro','"+callfunc("classname",17,"S","M")+"',$filecontents);

$filecontents = str_replace('arruaceira','"+callfunc("classname",17,"S","F")+"',$filecontents);

$filecontents = str_replace('arruaceiros','"+callfunc("classname",17,"P","M")+"',$filecontents);

$filecontents = str_replace('arruaceiras','"+callfunc("classname",17,"P","F")+"',$filecontents);

$filecontents = str_replace('alquimista','"+callfunc("classname",18,"S","M")+"',$filecontents);

$filecontents = str_replace('alquimistas','"+callfunc("classname",18,"P","M")+"',$filecontents);

$filecontents = str_replace('bardo','"+callfunc("classname",19,"S","M")+"',$filecontents);

$filecontents = str_replace('odalisca','"+callfunc("classname",19,"S","F")+"',$filecontents);

$filecontents = str_replace('bardos','"+callfunc("classname",19,"P","M")+"',$filecontents);

$filecontents = str_replace('odaliscas','"+callfunc("classname",19,"P","F")+"',$filecontents);

$filecontents = str_replace('s. aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('s. aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('super aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('super aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('S. aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('S. aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('Super aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('Super aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('s. Aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('s. Aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$filecontents = str_replace('super Aprendiz','"+callfunc("classname",23,"S","M")+"',$filecontents);

$filecontents = str_replace('super Aprendizes','"+callfunc("classname",23,"P","M")+"',$filecontents);

$fp = fopen($file, 'w');
if(!fwrite($fp, $filecontents)) {
echo "<font color=\"red\">O arquivo ".$file." n�o foi convertido</font><br>";
}
echo "<font color=\"green\">O arquivo ".$file." foi convertido</font><br>";
fclose($fp);
}
}
closedir($handle);
}

?>