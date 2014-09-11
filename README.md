Promet
=========
Local Traffic Monitor.

Version
----
1.0


Requirements
--------------
* Gcc
* Linux

How to use
--------------

```sh
git clone git@github.com:nkman/promet.git
cd promet
sudo su

gcc -o listen listen.c
./listen <protocol>

supported protocols are TCP, UDP, ICMP.
```

In Action
--------------

![alt Promet](https://raw.githubusercontent.com/nkman/promet/master/docs/pic.png)

License
----

MIT


**Free Software**
