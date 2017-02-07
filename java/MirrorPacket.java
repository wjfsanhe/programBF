public abstract class MirrorPacket{
    private static final int FORMAT_OVERHEAD_LEN=128;
    private static final int FORMAT_PAYLOAD_LEN=4;
    private static final int FORMAT_PAYLOAD_TYPE_LEN=2;

    public static final int PAYLOAD_VIDEO_BITSTREAM=0;
    public static final int PAYLOAD_CODEC_DATA=1;
    public static final int PAYLOAD_HEART_BEAT=2;
    public static final int PAYLOAD_UNKNOWN_TYPE=3;



    public  int payloadLen;
    public  int payloadType;

    public void setupPayloadInfo(int len,int type){
        payloadLen=len;
        payloadType=type;
    }
    public void pushBuffer(){
	System.out.println("parent Mirror output");
    }


}
