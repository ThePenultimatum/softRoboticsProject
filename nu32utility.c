/* NU32 Serial Bootloader Application
 * January 2015, Nick Marchuk
 * Combined Win, Mac, and Linux version
 *
 * On Win, make with: gcc nu32utility.c -o nu32utility -lwinmm
 * note: -lwinmm gets access to timeGetTime() from winmm.lib
 * To use, enter from comand line: nu32utility COMPORT HEXFILE
 * Type mode to get a list of available COMPORTs. Use the larger
 * of the two ports that appear when you plug in the NU32.
 * COMPORTs larger than COM9 must start with \\.\
 *
 * example: nu32utility COM5 myhex.hex
 *
 *
 *
 * On Mac and Linux, make with: gcc nu32utility.c -o nu32utility
 * To use, enter from the terminal: nu32utility COMPORT HEXFILE
 * Get a list of the available serial ports with: ls /dev/tty.*
 * the bootloader serial port name should look like /dev/tty.usbserial-xxxxxxxxB (not A)
 * 
 * example: ./nu32utility /dev/tty.usbserial-00001024B myhex.hex
*/

#include <stdio.h>
#include <stdlib.h> // for strtol

#if (defined(_WIN32) || defined(_WIN64))
  #include <windows.h> // for serial and time functions
#else
  #include <termios.h> // for serial
  #include <time.h> // for time functions
  #include <fcntl.h> // for serial constants
  #include <unistd.h> // for STDOUT_FILENO
  #include <string.h> // needed for memset
#endif

// special characters
#define SOH 0x01 // start of packet
#define EOT 0x04 // end of packet
#define DLE 0x10 // if SOH or EOT appears in data, preceed it with DLE

#define ARRAYLEN 400 // size of packet
#define ARRAYMAX 300 // max to put in packet, the smaller number

// CRC table
 int crc_table[16] = {
  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
  0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
};
int calc_CRC(char * message, int length);

#if (defined(_WIN32) || defined(_WIN64))
  // serial functions
  DWORD readFromSerialPort(HANDLE hSerial, char * buffer, int buffersize);
  DWORD writeToSerialPort(HANDLE hSerial, char * data, int length);
#endif

// call this program with 2 arguments: 
//      the name of the serial port, and the location of the hex file
int main(int argc, char *argv[]) {
  printf("\r\n=== NU32 Serial Bootloader ===\r\n");
  // check if the right number of args
  if (argc == 3) {
    printf(">Using com port: %s\r\n", argv[1]);
    printf(">Using hex file at: %s\r\n", argv[2]);
  }
  else {
    #if (defined(_WIN32) || defined(_WIN64))
      printf("Must be 3 args, example: nu32utility COM5 myhex.hex\n");
    #else
      printf("Must be 3 args, example: nu32utility /dev/tty.usbserial-00001024B myhex.hex\r\n");
    #endif
    printf("=== Bootloader program complete ===\r\n");
   return(0);
 }

  #if (defined(_WIN32) || defined(_WIN64))
    // open serial port
 LPCSTR portname = argv[1];
 DWORD  accessdirection = GENERIC_READ | GENERIC_WRITE;
 HANDLE hSerial = CreateFile(portname,
  accessdirection,
  0,
  0,
  OPEN_EXISTING,
  0,
  0);
 if (hSerial == INVALID_HANDLE_VALUE) {
  printf("Invalid serial port\n");
  printf("=== Bootloader program complete ===\n");
  return(0);
}
printf("Opened serial port %s\n",argv[1]);

    // set NU32 serial port parameters - 230400 baud, 8-1-n, RTS and CTS
DCB dcbSerialParams = {0};
dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
if (!GetCommState(hSerial, &dcbSerialParams)) {
  printf("Could not get serial port state\n");
}
dcbSerialParams.BaudRate=230400;
dcbSerialParams.ByteSize=8;
dcbSerialParams.StopBits=ONESTOPBIT;
dcbSerialParams.Parity=NOPARITY;
dcbSerialParams.fRtsControl = RTS_CONTROL_HANDSHAKE;
dcbSerialParams.fOutxCtsFlow = TRUE;
if(!SetCommState(hSerial, &dcbSerialParams)){
  printf("Some serial port setting error\n");
}
    // play with these if you get errors (numbers too small)
    // or if performance is too slow (numbers too big)
COMMTIMEOUTS timeouts={0};
    timeouts.ReadIntervalTimeout=2; // default 50
    timeouts.ReadTotalTimeoutConstant=2; // default 50
    timeouts.ReadTotalTimeoutMultiplier=2; // default 10
    timeouts.WriteTotalTimeoutConstant=2; // default 50
    timeouts.WriteTotalTimeoutMultiplier=2; // default 50
    if(!SetCommTimeouts(hSerial, &timeouts)){
      printf("Some serial timeout setting error\n");
    }
    
  #else
    // open serial port
    struct termios tio;
    //struct termios stdio;
    int tty_fd;

    // open serial port
    tty_fd=open(argv[1], O_RDWR | O_NONBLOCK); 

    if (tty_fd == -1) {
      printf("Invalid serial port\r\n");
      printf("=== Bootloader program complete ===\r\n");
      return(0);
    }

    if (!isatty(tty_fd)) {
      printf("Not a tty serial port\r\n");
      printf("=== Bootloader program complete ===\r\n");
      return(0);
    } 

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL|CRTSCTS; // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    cfsetospeed(&tio,B230400);
    cfsetispeed(&tio,B230400);

    // set serial parameters
    tcflush(tty_fd, TCIFLUSH);
    tcsetattr(tty_fd,TCSANOW,&tio);

    printf("Opened serial port %s\r\n",argv[1]); 
  #endif


  // function variables
  char array[ARRAYLEN];
  char single_hex_line[ARRAYLEN];
  int lines = 0;
  int length = 0;
  char * ptr_end;
  unsigned int line;
  int i=0,j=0,k=0;
  char hex[2];
  char message[ARRAYLEN]; // SOH+0x03+[HEX]+CRCL+CRCH+EOT 
  char message_buffer[ARRAYLEN]; // extra bytes needed for special characters
  int CRC;
  char response_buffer[50];
  char response[50];
  int response_index = 0;
  int response_length = 0;
  int moveOn = 0;
  int percent = 0;
  #if (defined(_WIN32) || defined(_WIN64))
    int startTime;
  #else
    clock_t startTime;
  #endif
  float complete;
  int nextPercent = 10;

  // send request for bootloader info, <SOH><0x01><CRCL><CRCH><EOT>
  printf(">Requesting bootloader version information...\r\n");
  message_buffer[0] = SOH;
  message_buffer[1] = DLE; // hardcoded for the following 0x01 == SOH
  message_buffer[2] = 0x01;
  CRC = calc_CRC(&message_buffer[2],1);
  message_buffer[3] = CRC&0xFF;
  message_buffer[4] = DLE; // hardcoded, the next one is always 16 (DLE)
  message_buffer[5] = (CRC>>8)&0xFF;
  message_buffer[6] = EOT;
  #if (defined(_WIN32) || defined(_WIN64))
    writeToSerialPort(hSerial, message_buffer, 7);
  #else
    write(tty_fd, message_buffer, 7);
  #endif
  
  // if bootloader info does not match or timeout, close serial and exit
  // bootloader info response, <SOH><0x01><MajorVer><MinorVer><CRCL><CRCH><EOT>
  moveOn = 0;
  response_index = 0;
  #if (defined(_WIN32) || defined(_WIN64))
    startTime = timeGetTime(); // in ms
  #else
    startTime = clock(); // in ticks
  #endif
    while(!moveOn) {
      #if (defined(_WIN32) || defined(_WIN64))
        response_length = readFromSerialPort(hSerial, response_buffer, 50);
      #else
        response_length = read(tty_fd, response_buffer, 50);
      #endif
      for(i=0;i<response_length;i++) {
        response[response_index] = response_buffer[i];
        response_index++;
      }
      for(i=0;i<response_index;i++) {
        if((i>6)&&(response[i]==EOT)&&(response[i-7]==SOH)) { // potential problem here w/ nu32 version
          moveOn = 1;
          printf("Bootloader detected, version %d.%d\r\n",response[i-4],response[i-3]);
          break;
         }
      }
  // if more than 2s wait, no bootloader is there, leave the program
  #if (defined(_WIN32) || defined(_WIN64))
 if(timeGetTime() - startTime > 2000) {
      // close the serial port
   CloseHandle(hSerial);
   printf("No bootloader detected!\n");
   printf("Serial port %s closed.\n",argv[1]);
      // exit
   printf("=== Bootloader program complete ===\n");
   return(0);
 }
  #else
 if(clock() - startTime > 2*CLOCKS_PER_SEC) {
      // close the serial port
   close(tty_fd);
   printf("No bootloader detected!\r\n");
   printf("Serial port %s closed.\r\n",argv[1]);
      // exit
   printf("=== Bootloader program complete ===\r\n");
   return(0);
 }
  #endif
}

  // send request to erase flash, <SOH><0x02><CRCL><CRCH><EOT>
printf(">Requesting flash erase...\r\n");
message_buffer[0] = SOH;
message_buffer[1] = 0x02;
CRC = calc_CRC(&message_buffer[1],1);
message_buffer[2] = CRC&0xFF;
message_buffer[3] = (CRC>>8)&0xFF;
message_buffer[4] = EOT;
  #if defined(_WIN32)
writeToSerialPort(hSerial, message_buffer, 5);
  #else
write(tty_fd, message_buffer, 5);
  #endif

  // wait for response or timeout
  // erase response, <SOH><0x02><CRCL><CRCH><EOT>
moveOn = 0;
response_index = 0;
  #if (defined(_WIN32) || defined(_WIN64))
    startTime = timeGetTime(); // in ms
  #else
    startTime = clock(); // in ticks
  #endif
    while(!moveOn) {
    #if (defined(_WIN32) || defined(_WIN64))
     response_length = readFromSerialPort(hSerial, response_buffer, 50);
  #else
     response_length = read(tty_fd, response_buffer, 50);
  #endif
     for(i=0;i<response_length;i++) {
      response[response_index] = response_buffer[i];
      response_index++;
    }
    for(i=0;i<response_index;i++) {
    if((response[i]==EOT)&&(response[i-1]!=DLE)) { // potential problem here
     moveOn = 1;
     printf("Flash erased!\r\n");
   }
 }
  // check to see if 4s has passed (erase takes a long time), quit 
  #if (defined(_WIN32) || defined(_WIN64))
 if(timeGetTime() - startTime > 4000) {
      // close the serial port
   CloseHandle(hSerial);
   printf("Could not erase flash!\n");
   printf("Serial port %s closed.\n",argv[1]);
      // exit
   printf("=== Bootloader program complete ===\n");
   return(0);
 }
  #else
 if(clock() - startTime > 4*CLOCKS_PER_SEC) {
      // close the serial port
   close(tty_fd);
   printf("Could not erase flash!\r\n");
   printf("Serial port %s closed.\n",argv[1]);
      // exit
   printf("=== Bootloader program complete ===\r\n");
   return(0);
 }
  #endif
}

  // try to open file, get number of lines
FILE *infile;
infile = fopen(argv[2],"r");
if(infile == NULL) {
  printf("Could not open file at %s!\r\n",argv[2]);
    // close the serial port
  #if (defined(_WIN32) || defined(_WIN64))
  CloseHandle(hSerial);
  #else
  close(tty_fd);
  #endif
  printf("Serial port %s closed.\r\n",argv[1]);
  // exit
  printf("=== Bootloader program complete ===\r\n");
  return(0);
}
  // loop thru file, get number of hex lines
while(fscanf(infile,"%s",array) != EOF) {
  lines++;
}
printf(">%d lines in file...\r\n",lines);
fclose(infile);

  // reopen file
infile = fopen(argv[2],"r");
if(infile == NULL) {
  printf("Could not open file at %s!\r\n",argv[2]);
    // close the serial port
  #if (defined(_WIN32) || defined(_WIN64))
  CloseHandle(hSerial);
  #else
  close(tty_fd);
  #endif
  printf("Serial port %s closed.\r\n",argv[1]);
  // exit
  printf("=== Bootloader program complete ===\r\n");
  return(0);
}

printf(">Programming...\r\n");
  printf("||||||||||\r\n"); // each bar represents 10% complete
  while(percent < lines) {
   for (i=0; i<ARRAYLEN;i++) {
     array[i] = 0;
     single_hex_line[i] = 0;
   }
    // read line and get number of characters in line
   length = 0;
   while(percent<lines & length < ARRAYMAX) {
     length = 0;
     fscanf(infile,"%s",single_hex_line);
     strcat(array,single_hex_line+1);
     percent++;
     while(array[length] != 0) {
      length++;
    }
    //printf("len = %d\n\r",length);
  }

  //printf("sing = %s\n\r", single_hex_line);
  //printf("arr  = %s\n\r", array);

    // build the message
  j = 0;
  message[j] = SOH;
  j++;
    message[j] = 0x03; // command to write hex line
    j++;
    for (i=0;i<length;i=i+2) { // start at 1 to skip the ':' at beginning of each line
      hex[0] = array[i];
    hex[1] = array[i+1];
      line = strtol(hex, &ptr_end, 16); // unhex the characters
      message[j] = line;
      j++;
    }
    CRC = calc_CRC(&message[1],j-1);
    message[j] = CRC&0xFF;
    j++;
    message[j] = (CRC>>8)&0xFF;
    j++;
    message[j] = EOT;
    j++;

    // double up for special charaters
    message_buffer[0] = message[0]; // SOH
    message_buffer[1] = message[1]; // 0x03
    k = 2;
    for (i=2;i<j-3;i++) {
      if((message[i]==SOH)||(message[i]==EOT)||(message[i]==DLE)) {
       message_buffer[k] = DLE;
       k++;
       message_buffer[k] = message[i];
     }
     else {
       message_buffer[k] = message[i];
     }
     k++;
   }
   if ((message[j-3]==SOH)||(message[j-3]==EOT)||(message[j-3]==DLE)) {
     message_buffer[k] = DLE;
     k++;
   }  
    message_buffer[k] = message[j-3]; // CRCL
    k++;
    if ((message[j-2]==SOH)||(message[j-2]==EOT)||(message[j-2]==DLE)) {
     message_buffer[k] = DLE;
     k++;
   }
    message_buffer[k] = message[j-2]; // CRCH
    k++;
    message_buffer[k] = message[j-1]; // EOT
    k++;

    // send message_buffer
  #if (defined(_WIN32) || defined(_WIN64))
    writeToSerialPort(hSerial, message_buffer, k);
  #else
    write(tty_fd, message_buffer, k);
  #endif

    // wait for response, <SOH><0x03><CRCL><CRCH><EOT>
    moveOn = 0;
    response_index = 0;
  #if (defined(_WIN32) || defined(_WIN64))
    startTime = timeGetTime(); // in ms
  #else
    startTime = clock(); // in ticks
  #endif
    while(!moveOn) {
    #if (defined(_WIN32) || defined(_WIN64))
     response_length = readFromSerialPort(hSerial, response_buffer, 50);
    #else
     response_length = read(tty_fd, response_buffer, 50);
    #endif
     for(i=0;i<response_length;i++) {
      response[response_index] = response_buffer[i];
      response_index++;
    }
    for(i=0;i<response_index;i++) {
      if((response[i]==EOT)&&(response[i-1]!=DLE)) { // potential problem here
       moveOn = 1;
     }
   }
    // if more than 2s wait, bootloader not responding, leave the program
    #if (defined(_WIN32) || defined(_WIN64))
   if(timeGetTime() - startTime > 2000) {
        // close the serial port
     CloseHandle(hSerial);
     printf("Could not program!\n");
     printf("Serial port %s closed.\n",argv[1]);
        // exit
     printf("=== Bootloader program complete ===\n");
     return(0);
   }
    #else
   if(clock() - startTime > 2*CLOCKS_PER_SEC) {
        // close the serial port
     close(tty_fd);
     printf("Could not program!\r\n");
     printf("Serial port %s closed.\r\n",argv[1]);
        // exit
     printf("=== Bootloader program complete ===\r\n");
     return(0);
   }
    #endif
 }
 complete = (float)percent / (float)lines * 100.0;
 if (complete >= nextPercent) {
    printf("*"); // show a moving bar of '*' as each line is programmed
    fflush(stdout);
    nextPercent = nextPercent + 10;
  }
}
printf("\nProgramming complete!\r\n");

  // close the file
fclose(infile);

  // request jump to application, <SOH><0x05><CRCL><CRCH><EOT>
printf(">Requesting jump to application...\r\n");
message_buffer[0] = SOH;
message_buffer[1] = 0x05;
CRC = calc_CRC(&message_buffer[1],1);
message_buffer[2] = CRC&0xFF;
message_buffer[3] = (CRC>>8)&0xFF;
message_buffer[4] = EOT;
  #if defined(_WIN32)
writeToSerialPort(hSerial, message_buffer, 5);
  #else
write(tty_fd, message_buffer, 5);
  #endif

  // close serial port
  #if (defined(_WIN32) || defined(_WIN64))
CloseHandle(hSerial);
  #else
close(tty_fd);
  #endif
printf("Serial port %s closed.\r\n",argv[1]);

  // exit
printf("=== Bootloader program complete ===\r\n");
return(0);
}

#if (defined(_WIN32) || defined(_WIN64))
  // serial read function
DWORD readFromSerialPort(HANDLE hSerial, char * buffer, int buffersize) {
  DWORD dwBytesRead = 0;
  if(!ReadFile(hSerial, buffer, buffersize, &dwBytesRead, NULL)){
    printf("Some serial read error\n");
  }
  return dwBytesRead;
}

  // serial write function
DWORD writeToSerialPort(HANDLE hSerial, char * data, int length) {
  DWORD dwBytesRead = 0;
  if(!WriteFile(hSerial, data, length, &dwBytesRead, NULL)){
    printf("Some serial write error\n");
  }
  return dwBytesRead;
}
#endif

// calculate the CRC
int calc_CRC(char * message, int length) {
  int i;
  int crc = 0;
  int j = 0;

  for (j=0;j<length;j++) {
    i = (crc >> 12) ^ (message[j] >> 4);
    crc = crc_table[i & 0x0F] ^ (crc << 4);
    i = (crc >> 12) ^ (message[j] >> 0);
    crc = crc_table[i & 0x0F] ^ (crc << 4);
  } 

  return (crc & 0xFFFF);
}

/* EOF */

