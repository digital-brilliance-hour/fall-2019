@echo off
title Using Imagemagick to convert image backgrounds
echo Finding PNGS...
FOR /R %%I IN (*.png) DO convert "%%I" -background "rgb(255,0,255)" -flatten "%%I"
GOTO :eof

:subroutine
echo converting %1
convert %1 -background "rgb(255,0,255)" -flatten %1
GOTO :eof
