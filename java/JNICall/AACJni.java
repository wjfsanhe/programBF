public class AACJni{

    //native method
    public native int InitAACDecoder(final String[] format);

    public native int AACDecoderGetStatus();

    public native int AACDecodeFrame(byte[] AACBytes,int[] pcmSamples,int samplesPerFrame);
 
 public static void main(String[] args) {
  System.loadLibrary("Sample1");
 }

}
