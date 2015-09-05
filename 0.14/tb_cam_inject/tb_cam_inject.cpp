//***************************************
//******** TOOBIT CAM INJECTION *********
//***************************************
//
//	More info watch Youtube videos
//		https://www.youtube.com/playlist?list=PLmSUTHzWYMaNGqxUQunqIu3TbsDL2QnI-
//		
//		More Mad science and
//		  technology art
//			http://www.dscript.org
#include <stdio.h>
#include <iostream>
#include <sys/types.h> 
#include <netdb.h>      
#include <unistd.h> 
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define TOOBIT_SERVER_IP 		"192.168.0.103"
#define TOOBIT_SERVER_PORT 		3337
#define TOOBIT_X			400
#define TOOBIT_Y			400
#define TOOBIT_XY			(TOOBIT_X	*	TOOBIT_Y)
#define TOOBIT_INJECT_DATA_SZIE		(TOOBIT_XY	+	1	)
#define TOOBIT_BROADCAST_BUFFER		1000000

using namespace cv;
using namespace std;

char cmd_str[]="GET /I";
char cmd_len=6;
char last_char=0;

int got_p=0;
uint16_t rbytes[256];

Mat frame_mat;

#define RCVBUFSIZE 32   /* Size of receive buffer */


//filter the mat and send it to server
void filter_mat(){
  uint8_t* pixdat=(uint8_t *)frame_mat.data;
  unsigned int r_c=frame_mat.rows, r_n, c_c=frame_mat.cols, c_n, tot,i,try_write;
  int sock, ret, write_size, write_tries;
  char abc_123=0,pixv, broadcast[TOOBIT_BROADCAST_BUFFER], *bnow=broadcast+(r_c*c_c)+1;
  struct sockaddr_in server_addr; 

  broadcast[0]=0;
  r_n=r_c;
  while(r_n--){
    c_n=c_c;
    while(c_n--){
      if(++abc_123>3)abc_123=0;
      if(abc_123==3){pixv=pixdat[0]; }else{ pixv=pixdat[abc_123];}
      if(pixv>50&&pixv>=pixdat[0]&&pixv>=pixdat[1]&&pixv>=pixdat[2]){
	pixdat[0]=pixdat[1]=pixdat[2]=255;
	*--bnow=42;
	}else{
	*--bnow=32;
	pixdat[0]=pixdat[1]=pixdat[2]=0;
	}
      pixdat+=3;
      }
    }

    if((sock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0){
      printf("sock error 1\n");
      return;
      }

    memset(&server_addr, 0, sizeof(server_addr));   
    server_addr.sin_family      = AF_INET;            
    server_addr.sin_addr.s_addr = inet_addr(TOOBIT_SERVER_IP);
    server_addr.sin_port        = htons(TOOBIT_SERVER_PORT);


  if(connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    printf("sock error 2\n");
    close(sock);
    return;
    }

  if(send(sock,cmd_str,6,0)!=6){
    printf("sock error 3\n");
    close(sock);
    return;
    }

  write_size=0;write_tries=10;
  while(write_size<TOOBIT_INJECT_DATA_SZIE&&write_tries--){
    try_write=TOOBIT_INJECT_DATA_SZIE-write_size;
    ret=send(sock, broadcast+write_size, try_write, MSG_NOSIGNAL);
    if(ret>0)write_size+=ret;
    }

  shutdown(sock,SHUT_RDWR);
  close(sock);
  return;
  }

//main
int main(){	
  setbuf(stdout,NULL);
  cv::VideoCapture webcam(0);
  if(!webcam.isOpened()){printf("failed ot open webcam");return 0;}
  while(1){
    webcam >> frame_mat;
    resize(frame_mat, frame_mat, Size(TOOBIT_X, TOOBIT_Y));
    filter_mat(); //-----------------------------------actually filters and sends to server
    imshow("stream", frame_mat);
    waitKey(1);
    }
  return 1;
}
