![SofleKeyboard default keymap](https://github.com/josefadamcik/SofleKeyboard/raw/master/Images/soflekeyboard.png)
![SofleKeyboard adjust layer](https://github.com/josefadamcik/SofleKeyboard/raw/master/Images/soflekeyboard_layout_adjust.png)


# Brian's keymap for Sofle Keyboard

Should mirror the layout for [Moonlander](https://configure.zsa.io/moonlander/layouts/bnYbg/latest/0)

```bash
cd qmk/qmk_firmware
source bin/activate
## edit files
qmk compile
## open up qmk toolbox
## disconnect USBC; disconnect TRRS cable
## reconnect each half separately; for each half, double-tap the reset button until you see "Device Connected" in QMK toolbox. Then flash.
```
