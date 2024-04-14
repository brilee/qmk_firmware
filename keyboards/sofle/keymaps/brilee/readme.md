![SofleKeyboard default keymap](https://github.com/josefadamcik/SofleKeyboard/raw/master/Images/soflekeyboard.png)
![SofleKeyboard adjust layer](https://github.com/josefadamcik/SofleKeyboard/raw/master/Images/soflekeyboard_layout_adjust.png)


# Brian's keymap for Sofle Keyboard

Should mirror the layout for [Moonlander](https://configure.zsa.io/moonlander/layouts/bnYbg/latest/0)

```bash
brew install qmk/qmk/qmk
qmk setup
```

```bash
cd qmk/qmk_firmware
source bin/activate
## edit files
qmk compile -kb sofle -km brilee
qmk compile -e CONVERT_TO=promicro_rp2040 -kb sofle -km brilee


## open up qmk toolbox, select sofle_rev1_brilee.hex, select ATmega32U4.
## disconnect USBC; disconnect TRRS cable
## reconnect each half separately; for each half, double-tap the reset button until you see "Device Connected" in QMK toolbox. Then flash.
```
