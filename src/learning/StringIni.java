public class StringIni {

    //native method
    public native String GetStringUTFCharsFunc(String input);
    public native String GetStringLengthAndRegionFunc(String input);
    public native int GetIntArrayRegionFunc(int size);

    //static initializer
    static {
        System.loadLibrary("libNativeStr");
    }
    public static void main(String[] args){
        StringIni si = new StringIni();
        String output = si.GetStringUTFCharsFunc("Enter your name: ");
        System.out.println("this is your name right? "+output);
        output = si.GetStringLengthAndRegionFunc("Enter your name: ");
        System.out.println("this is your name right? "+output);
        int sum = si.GetIntArrayRegionFunc(3);
        System.out.println("the total sum is: "+sum);
    }
}
