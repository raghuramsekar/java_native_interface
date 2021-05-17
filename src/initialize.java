public class initialize {

    //Generic rights
    public static final int GENERIC_ALL = 268435456;
    public static final long GENERIC_READ = 2147483648L;
    public static final int GENERIC_EXECUTE = 536870912;
    public static final int GENERIC_WRITE = 1073741824;

    //standard rights
    public static final int DELETE = 65536;
    public static final int READ_CONTROL = 131072;
    public static final int WRITE_DAC = 262144;
    public static final int WRITE_OWNER = 524288;

    //specific rights
    public static final int FILE_READ_ATTRIBUTES = 128;
    public static final int FILE_WRITE_ATTRIBUTES = 256;
    public static final int FILE_EXECUTE = 64;
    public static final int FILE_WRITE_EA = 16;
    public static final int FILE_READ_EA = 8;
    public static final int FILE_READ_DATA = 1;
    public static final int FILE_WRITE_DATA = 2;
    public static final int FILE_APPEND_DATA = 4;





    //Access Type Header
    public static final int ACCESS_ALLOWED_ACE_TYPE = 0;
    public static final int ACCESS_DENIED_ACE_TYPE = 1;
    

    public void access_mask_print(long access_mask){

        if((access_mask & GENERIC_ALL) == GENERIC_ALL){
            System.out.println("GENERIC_ALL");
        }
        if((access_mask & GENERIC_READ) == GENERIC_READ){
            System.out.println("GENERIC_READ");
        }
        if((access_mask & GENERIC_EXECUTE) == GENERIC_EXECUTE){
            System.out.println("GENERIC_EXECUTE");
        }
        if((access_mask & GENERIC_WRITE) == GENERIC_WRITE){
            System.out.println("GENERIC_WRITE");
        }
        if((access_mask & DELETE) == DELETE){
            System.out.println("DELETE");
        }
        if((access_mask & READ_CONTROL) == READ_CONTROL){
            System.out.println("READ_CONTROL");
        }
        if((access_mask & WRITE_DAC) == WRITE_DAC){
            System.out.println("WRITE_DAC");
        }
        if((access_mask & WRITE_OWNER) == WRITE_OWNER){
            System.out.println("WRITE_OWNER");
        }
        if((access_mask & FILE_READ_ATTRIBUTES) == FILE_READ_ATTRIBUTES){
            System.out.println("FILE_READ_ATTRIBUTES");
        }
        if((access_mask & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES){
            System.out.println("FILE_WRITE_ATTRIBUTES");
        }
        if((access_mask & FILE_EXECUTE) == FILE_EXECUTE){
            System.out.println("FILE_EXECUTE");
        }
        if((access_mask & FILE_WRITE_EA) == FILE_WRITE_EA){
            System.out.println("FILE_WRITE_EA");
        }
        if((access_mask & FILE_READ_EA) == FILE_READ_EA){
            System.out.println("FILE_READ_EA");
        }
        if((access_mask & FILE_READ_DATA) == FILE_READ_DATA){
            System.out.println("FILE_READ_DATA");
        }
        if((access_mask & FILE_WRITE_DATA) == FILE_WRITE_DATA){
            System.out.println("FILE_WRITE_DATA");
        }
        if((access_mask & FILE_APPEND_DATA) == FILE_APPEND_DATA){
            System.out.println("FILE_APPEND_DATA");
        }
    }

    public void aceType_print(int aceType,long access_mask,String AccName){
        if((aceType & ACCESS_ALLOWED_ACE_TYPE) == ACCESS_ALLOWED_ACE_TYPE){
            System.out.println("Permission granted to: "+AccName);
            access_mask_print(access_mask);
        }
        if((aceType & ACCESS_DENIED_ACE_TYPE) == ACCESS_DENIED_ACE_TYPE){
            System.out.println("Permission denied to: "+AccName);
            access_mask_print(access_mask);
        }
    }

}
