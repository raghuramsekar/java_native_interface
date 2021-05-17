import java.text.*;
import java.util.*;
import java.util.Locale;
import java.lang.*;

public class Caller {

    public static long FileCreated;
    public static long FileAccessed;
    public static long FileModified;
    public static long FileSizeInBytes;
    public static boolean ReadOnly;
    public static boolean Hidden;
    public static long FileSizeInDisk;
    public static String[] ACL_HEADER_AccName;
    public static int[] ACL_HEADER_AceType;
    public static int[] ACE_Entries;


    //static library linking
    static {
//        GENERIC_FILE_ALL = 31;
        System.loadLibrary("nativeLib");
        System.loadLibrary("accessSec");
    }

    //native function call
    private native HashMap<Object,Object> nativeFunc(String filePath);
    private native HashMap<Object,Object> accessSecFunc();

    //main function
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter file name: ");
        String FileName = sc.nextLine();

        Caller c1 = new Caller();
        HashMap<Object,Object> hash =  c1.nativeFunc(FileName);
        for(Object key:hash.keySet()) {
            if(key.equals("FileCreated")){
                FileCreated =(long) hash.get(key);
            }
            if(key.equals("FileAccessed")){
                FileAccessed =(long) hash.get(key);
            }
            if(key.equals("FileModified")){
                FileModified = (long)hash.get(key);
            }
            if(key.equals("FileSizeInBytes")){
                FileSizeInBytes = (long)hash.get(key);
            }
            if(key.equals("ReadOnly")){
                ReadOnly = (boolean)hash.get(key);
            }
            if(key.equals("Hidden")){
                Hidden = (boolean)hash.get(key);
            }
        }

        int lastOccurrence = FileName.lastIndexOf('.');
        String FileExtension = FileName.substring(lastOccurrence+1);
        if(FileExtension.equalsIgnoreCase("txt")){
            System.out.println("This is information file");
        }

        //File created
        Date d = new Date(FileCreated*1000-(3*24*60*60*1000));
        DateFormat df = new SimpleDateFormat("dd MMM yyyy hh:mm:ss zzz", Locale.ENGLISH);
        System.out.println("File created in: "+df.format(d));

        //File Accessed
        d = new Date(FileAccessed*1000);
        df = new SimpleDateFormat("dd MMM yyyy hh:mm:ss zzz", Locale.ENGLISH);
        System.out.println("File Accessed in: "+df.format(d));

        //File Modified
        d = new Date(FileModified*1000);
        df = new SimpleDateFormat("dd MMM yyyy hh:mm:ss zzz", Locale.ENGLISH);
        System.out.println("File Modified in: "+df.format(d));

        //is file read-only
        System.out.println("Is File Read only: "+ReadOnly);

        //is file hidden
        System.out.println("Is File Hidden: "+Hidden);

        //File size in bytes
        System.out.println("File size in bytes: "+FileSizeInBytes);

        //file size in disk
        if(FileSizeInBytes<1024){
            System.out.println("File size in disk in bytes is :1");
        }
        else{
            long calc = (FileSizeInBytes / 4096) + 1;
            FileSizeInDisk = calc * 4096;
            System.out.println("File size in disk in bytes is : "+FileSizeInDisk);
        }

        initialize ini = new initialize();
        hash = c1.accessSecFunc();

        int[] acetype = (int[])hash.get("ACL_HEADER_AceType");
        int[] aceentries = (int[])hash.get("ACE_Entries");
        String[] accname = (String[])hash.get("ACL_HEADER_AccName");

        for(int i=0;i<acetype.length;i++){
            ini.aceType_print(acetype[i],aceentries[i],accname[i]);
        }


       sc.close();
    }
}
