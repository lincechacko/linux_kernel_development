root@beaglebone-yocto:~# echo "hello world" > /proc/new_dir/lince

root@beaglebone-yocto:~# cat /proc/new_dir/lince 

hello world

root@beaglebone-yocto:~# dmesg | tail

[  254.592950] procfs_kernel: loading out-of-tree module taints kernel.

[  254.598761] major and minor number creation success

[  254.602369] cdev init success

[  254.605008] adding the character driver to the system is success

[  254.609875] struct class creation success

[  254.619180] module has been added succssfully

[  264.224393] proccess file open called

[  264.226941] process file close called

[  275.961339] proccess file open called

[  275.990091] process file close called
