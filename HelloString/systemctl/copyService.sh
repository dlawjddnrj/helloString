#!/bin/bash
echo "service file copying ..."
directory='/lib/systemd/system'

sudo cp hel* $directory

helbus='helbus.service'
helclientA='helclient_a.service'
helclientB='helclient_b.service'
helserver='helserver.service'

serviceArray=('helbus.service' 'helclient_a.service' 'helclient_b.service' 'helserver.service')


for ((var = 0; var < 4; var++))
do
	findVar=$(find $directory -name ${serviceArray[$var]})
	
	tempFindResult=${findVar:20}
	tempService=${serviceArray[$var]}
	
	if [ ${tempFindResult} == ${tempService} ]; then
		copyResult=1
	else
		copyResult=0
		echo "not found Service File Name :" ${serviceArray[$var]} "(파일이 없을 경우 단항 연산자 예상됨이 발생)"
	fi
done

if [ $copyResult -eq 1 ]; then
	echo "copy Success !"
else
	echo "copy Failure ..."
fi
