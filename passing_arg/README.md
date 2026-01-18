root@beaglebone-yocto:~# insmod param_passing.ko valueNew=34 nameNew="test" arr_valueNew=10,11,12,13

root@beaglebone-yocto:~# dmesg|tail

[   14.169356] 8021q: adding VLAN 0 to HW filter on device eth0

[  592.742747] param_passing: loading out-of-tree module taints kernel.

[  592.748522] ValueNew = 34  

[  592.750044] cb_valueNew = 0  

[  592.752581] NameNew = test 

[  592.754105] Arr_value[0] = 10

[  592.755780] Arr_value[1] = 11

[  592.757450] Arr_value[2] = 12

[  592.759121] Arr_value[3] = 13

[  592.761392] Kernel Module Inserted Successfully...

root@beaglebone-yocto:~# echo 99 > /sys/module/param_passing/parameters/cb_valueNew 

root@beaglebone-yocto:~# dmesg|tail

[  592.748522] ValueNew = 34  

[  592.750044] cb_valueNew = 0  

[  592.752581] NameNew = test 

[  592.754105] Arr_value[0] = 10

[  592.755780] Arr_value[1] = 11

[  592.757450] Arr_value[2] = 12

[  592.759121] Arr_value[3] = 13

[  592.761392] Kernel Module Inserted Successfully...

[  663.493730] Call back function called...

[  663.496410] New value of cb_value = 99
