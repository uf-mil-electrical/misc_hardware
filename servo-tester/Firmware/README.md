# Firmware
Stores all code and build files

For this CoTS board, we will be using a Pico, which requires installing the Pico C SDK. The steps can be found in [`../Planning/getting-started-with-pico.pdf`](../Planning/getting-started-with-pico.pdf), and they expect you to use a Debian-base Linux Distro. There are steps for Windows, but it is significantly easier on Linux. 

## If you are going to modify the code on VS Code
- If you plan on modifing the code on VS Code, open `Firmware/` instead of the whole git repo.
  -  `.vscode/` only will load if it is located within the root of the folder opened; however, I do not want it to conflict with other people's work.

## How to upload code
- Make sure to install the SDK (PDF Chapter 2)
  - The rest is taken from the PDF Chapter 3 or 6
- `$ cd build`
- `$ export PICO_SDK_PATH=$HOME/pico/pico-sdk`
- `$ cmake ..`
- `$ make`
- unplug the pico (if already plugged in), press the boot button on the pico, and plug it in again while pressing the button
- if this is your first time doing anything with the Pico, do `$ sudo mkdir /mnt/pico`
- `$ sudo mount /dev/sda1 /mnt/pico/`
  - if sda1 doesn't exist, do `$ dmesg | tail` and look for what `sdX` has `Attached SCSI removable disk` then do `$ sudo mount /dev/sdX1 /mnt/pico/`
- `$ cp *.uf2 /mnt/pico/`
- `$ sudo umount /mnt/pico/`

## How to get serial output
#### Method 1: VS Code Serial (Easier)
1. Install Serial Monitor Extension in VS Code
2. Open Serial Monitor
3. Port `/dev/ttyACM0 - Raspberry Pi`
4. Baud rate `115200`
5. Click `Start Monitoring`
   
#### Method 2: Minicom
1. install minicom with apt
   - `$ sudo apt install minicom`
2. `$ minicom -b 115200 -o -D /dev/ttyACM0`
3. To exit `Ctrl + A` then `X`

### Add yourself to the dialout group
- You need to run the following command, log out, and log back in to have access to the serial monitor device
  - `$ sudo usermod -a -G dialout $USER`