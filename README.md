# KatroLogger
KeyLogger for Linux Systems.

- **Dependencies**
  - curl
  - libx11-dev (Debian-Based)
  - libX11-devel (RHEL-Based)

- **Compiling**
```
./configure
make
make install
```
- **Usage**
```
keylogger --output /path/<file>
```
Send data by e-mail:
```
keylogger --smtp-help
```
- **Uninstall**
```
make uninstall
```
