
 public class MirrorStreamPacket extends MirrorPacket {

        public byte[] stream;
        //private int payloadType=PAYLOAD_VIDEO_BITSTREAM;

       /* public void MirrorStreamPacket(int len){
            payloadLen=len;
        }*/
        public void pushBuffer(){
                System.out.println("stream push buffer");
        }
    }

