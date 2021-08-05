MIFARE Classic Tool Clone dan Erased 
=========================

Kebutuhan hardwere :
* Nodemcu ESP8266
* MFRC522

Cara kerja
----------
* Ketika sudah di nyalakan di tandai led pada MFRC522 telah menyala.
* Pertama tempelkan kartu pertama maka led pada ESP8266 akan berkedip dan menyala terus, sebagai tanda data kartu sudah tersimpan, (kemudian lepaskan kartu pertama).
* Selanjutnya tempelkan kartu master untuk clone (sesui UID yang sudah di daftarkan di program), sampai led pada ESP8266 berudah berkedip stabil tiap detik, sebagai tanda siap untuk melakukan clone kartu ke kartu baru (syarat writable).
* Kemudian tempelkan kartu clone nya, apa bila led mati tandanya clone berhasil, dan apabila led berkedip sangat cepat dan kemudian mati berarti gagal kemungkinan kartu tidak writable.
* Ada fitur untuk mereset/hapus block 0 bisa di lihat di scriptnya.

Perhatian
----------
* Prcobaan ini hanya media untuk pembelajaran.
* Prose yang dilakukan hanya bekerja pada block 0 atau pada manufactur block atau pada UID tidak pada block data.

## Copyright
Copyright © 2021 Candra Rudi.

The MIT License (MIT)
