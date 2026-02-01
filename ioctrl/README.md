root@beaglebone-yocto:~# ./user_app 

Opening Driver


Enter the Value to send

1245

Writing Value to Driver

Reading Value from Driver

Value is 1245

Closing Driver

root@beaglebone-yocto:~# dmesg|tail

[  254.619180] module has been added succssfully

[  264.224393] proccess file open called

[  264.226941] process file close called

[  275.961339] proccess file open called

[  275.990091] process file close called

[ 1417.251121] allocation of major and minor number is success

[ 1417.257667] kernal module added successfully

[ 1549.431883] Device File Opened...!!!

[ 1555.644374] Value = 1245

[ 1555.645814] Device File Closed...!!!
