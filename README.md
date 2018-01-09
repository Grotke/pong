# Pong
Pong was created in C++ to get familiar with SFML, game architecture and rapid development.

It has the option of playing AI vs AI, AI vs Player or Player vs Player with two people at the same keyboard.

For a postmortem where I talk about what I learned while developing Pong (surprisingly more than I expected), read [Pong Postmortem](http://www.josephcmontgomery.com/blog/postmortem-pong)

![Play](http://www.josephcmontgomery.com/uploads/4/5/8/3/45834621/pong-fixed_orig.gif)

## Audio Warning
Just to warn you, the audio isn't adjustable or muteable in game and will be pretty loud. Didn't get around to implementing adjustable audio and probably never will.

## Controls
R does a soft reset which resets the paddles and ball but not the scores.

The up and down arrow keys control the right paddle.

W and S control the left paddle.

Esc brings up the options menu.

## How to Build
Built with Visual Studio 2017 15.5.2. Just open the solution file (pong.sln) in VS and build it from there. 

## Built With
Libraries included in libs/

* [SFML](https://www.sfml-dev.org/) - Used for 2D graphics, input and audio handling
* [TGUI](https://tgui.eu/) - GUI library for SFML

Audio created by me in
* [FL Studio](https://www.image-line.com/flstudio/) - Music production environment

## Deployment
To create a standalone project:

1. Build the release version of Pong in Visual Studio. Executable should be in pong/Release. Copy it to its own folder.
2. Copy all the dlls from libs\SFML-2.4.2-windows-vc14-32-bit\SFML-2.4.2\bin into the same folder as pong.exe.
3. Copy tgui.dll from libs\TGUI-0.7.5-vc14-32bit-for-SFML-2.4.2\TGUI-0.7\lib into the same folder as pong.exe.
4. Copy sounds/ and oswald.ttf from pong/ into the same folder as pong.exe.

You should now be able to run the executable and start playing Pong.
