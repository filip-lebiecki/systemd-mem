[Youtube Video](https://youtu.be/N7mGchZkHGQ?si=6A3ZMB3roUiGNzHa)

# systemd-mem

```
gcc memleak.c -o memleak
gcc allocmem.c -o allocmem
```


### Memory total, used and available

```
grep -i memtotal /proc/meminfo
cat /proc/meminfo
free -b
free -m
```

### Cache

```
ls -lh file1G  
hyperfine -r1 "dd if=file1G of=/dev/null"
free -m
hyperfine -r1 "dd if=file1G of=/dev/null"
stress-ng --vm 1 --vm-bytes 3G --vm-keep
free -m
```

### Memory free

```
free -m
dd if=file1G of=/dev/null
free -m
sysctl -w vm.drop_caches=3
echo 3 > /proc/sys/vm/drop_caches
free -m
```

### Swap

```
swapon --show
free -m
stress-ng --vm 1 --vm-bytes 5G --vm-keep
htop
```

### Memory resident, virtual

```
stress-ng --vm 1 --vm-bytes 5G --vm-keep
htop
sysctl vm.swappiness
```

### Memory overcommitment 

```
sysctl -w vm.overcommit_memory=1
htop
./allocmem 8000
htop F4 allocmem
alloc ENTER
htop
```

### OOM Killer

```
dmesg | tail -1
sysctl -w vm.overcommit_memory=2
./allocmem 8000
sysctl -w vm.overcommit_memory=0
sysctl -w vm.overcommit_memory=2
./allocmem 8000
htop F4 allocmem
```

### SystemD memory max limit

```
swapoff -a
free -m
systemctl edit --force --full mem.slice
[Unit]
Description=Memory limit
[Slice]
MemoryMax=1000M
cat /etc/systemd/system/mem.slice
systemctl daemon-reload
systemctl start mem.slice
systemctl cat memleak.service
systemctl start memleak
watch -n1 "systemctl status memleak"
systemctl edit --force --full memleak.service
Slice=mem.slice
systemctl daemon-reload
watch -n1 systemctl status mem.slice
systemctl start memleak
swapon -a
free -m
watch -n1 systemctl status mem.slice
systemctl start memleak
show watch
systemctl edit --force --full mem.slice
MemorySwapMax=500M
systemctl daemon-reload
watch -n1 systemctl status mem.slice
2: systemctl start memleak
show watch
```

### SystemD memory high limit

```
swapoff -a
systemctl edit --force --full mem.slice
MemoryHigh=900M
systemctl daemon-reload
watch -n1 systemctl status mem.slice
systemctl start memleak
htop, filter memleak
```
