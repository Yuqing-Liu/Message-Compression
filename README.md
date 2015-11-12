# Message-Compression
# Task
This program encodes a message(ASCI, BMP, etc.) using lossless compression. The encoded message is at least 5% smaller than the original, and provides accurate decoding.
# Thoughts
The encoder.cpp first reads in the file in binary numbers, then groups every 8 bits as the corresponding character. Based on the Huffman encoding method, all characters' frequencies are counted and put into the leaf nodes of a binary heap. Therefore, less frequent characters take less than 8 bit to encode. All the encoded characters are lined up in encodedMessage.
After the Huffman tree is built, the decoder.cpp take the encodedMessage and restore the 8 bit binary numbers of each charater in the message in order.
# Source
"encoderRunner.cpp" is written by Professor Sean Davis. It returns the the compressed file size and CPU time to test the efficiency.
Professor Sean Davis also provided the basic structure of "encoder.h" and "encoder.h". 
Weiss code, "BinaryHeap", is directly used in my program. 
