# I2C-Bus-extender
extend the range of I2C connections by modulating with an active driver, allows for 200m distance

Principally I like the I2C bus, and it is very widely used to talk between components on a pcb level. But higher capacitance and inducted RF puts the little guy at risk to loose data. So I put some effort in understanding the limits, and it came clear that there is a significant improvement inside a comparetment if you increase the current on the bus by having proper pull up resistors. 4k7 is the default for 5V bus. on 3v3 bus better 2k2. i1k seems the maximum the usual semis can drive to zero. But the shape when looked on the oscillopscope is greatly improved.

## Leaving the box

well, connecting anything to this bus outside of the case is putting the board at risk, and endangers the integrity of the bus. Therefore it is useful to transform the signal to a more robust bus like modbus,can bus or similar. But that is quite a task, one must define new commands, implement converters,etc. whatever.

The solution came from TI having a bus driver developed exactly for the purpose

### P82B96

[Datasheet](https://www.ti.com/lit/ds/symlink/p82b96.pdf?ts=1593359005466&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FP82B96%253Futm_source%253Dgoogle%2526utm_medium%253Dcpc%2526utm_campaign%253Dasc-null-null-GPN_EN-cpc-pf-google-eu%2526utm_content%253DP82B96%2526ds_k%253DP82B96%2526DCM%253Dyes%2526gclid%253DCjwKCAjw_-D3BRBIEiwAjVMy7G5qxsvwfxLvoI9qvvvXimi5iXlMqIplM2xG1SZRruiqwSxxvto6rhoCjSkQAvD_BwE%2526gclsrc%253Daw.ds)

It allows us to simpla inject 12V on either side of the comm, and get a very robust signal to go far away and be stable. Also each 3v3 bus of both participants remain integer and unaffected by each other electrically. I didnt go that far to make it galvanic seperated, as my test shows really robust behaviour with its simplest implementation.

So I put that chip on a small breakout with a D-SUB9 female connector attached to mount it on a backplane.

### Breakout Connector

original use case was to connect the Hermes-Lite 2 to my homebrew PA500. But I use it now also to wire my mast sensor over 20m distance to the controller. The PCB is very flexible and multi purpose. It allows to jumper different signals to that D-SUB9 cable. 

