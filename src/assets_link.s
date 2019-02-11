# To Be Continued 1.0.0 (C) Karim 'TheSola10' Vergnes
# License: GNU GPL 3.0
# File to link assets statically into executable

.section .data
.global arr_png
.type arr_png, @object
.align 8

arr_png:
.incbin "assets/arr.bmp"

.global arr_png_size
.type arr_png_size, @object
.align 8
arr_png_size:
.int arr_png_size - arr_png


.global tbc_wav
.type tbc_wav, @object
.align 8

tbc_wav:
.incbin "assets/tbc.wav"

.global tbc_wav_size
.type tbc_wav_size, @object
.align 8
tbc_wav_size:
.int tbc_wav_size - tbc_wav
