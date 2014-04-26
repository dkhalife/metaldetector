#line 1 "H:/PIC Projects/Metal Detector/picoDetector.c"


unsigned char i;
unsigned char ctr ;
unsigned char previous ;
unsigned char calibr ;
unsigned char restarts ;
unsigned char en ;
#line 13 "H:/PIC Projects/Metal Detector/picoDetector.c"
void main(){
#line 17 "H:/PIC Projects/Metal Detector/picoDetector.c"
 CMCON = 7 ;
 TRISIO = 0 ;
 GPIO = 0 ;
#line 24 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if(STATUS.NOT_TO){
#line 28 "H:/PIC Projects/Metal Detector/picoDetector.c"
 restarts = 0 ;
 calibr = 1 ;
 }
#line 35 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if(restarts < 255) restarts++ ;
#line 40 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if((previous ^ ctr) > calibr){
#line 44 "H:/PIC Projects/Metal Detector/picoDetector.c"
 GPIO.F0 = en ;
#line 49 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if(STATUS.NOT_TO == 0){
#line 53 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if(restarts <  50 ){
#line 58 "H:/PIC Projects/Metal Detector/picoDetector.c"
 calibr <<= 1 ;
 Delay_ms(5);
 }
 }
 else{
#line 66 "H:/PIC Projects/Metal Detector/picoDetector.c"
 GPIO.F0 = 0 ;
 }
 }
#line 73 "H:/PIC Projects/Metal Detector/picoDetector.c"
 previous = ctr ;
#line 78 "H:/PIC Projects/Metal Detector/picoDetector.c"
 if(restarts >  50 ){
#line 83 "H:/PIC Projects/Metal Detector/picoDetector.c"
 GPIO.F1 = 0 ;
 en = 1 ;
 }
 else{
#line 91 "H:/PIC Projects/Metal Detector/picoDetector.c"
 GPIO.F1 = 1 ;
 en = 0 ;
 }
#line 98 "H:/PIC Projects/Metal Detector/picoDetector.c"
 OPTION_REG = 0b11111001 ;
#line 103 "H:/PIC Projects/Metal Detector/picoDetector.c"
 ctr = 0 ;
 while(1){
 ctr++ ;
 }
}
