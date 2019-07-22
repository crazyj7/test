package com.my.app ;

public class testNative {
        native public static void hello() ;
	native public String greeting(String name) ;
		
        static {
                System.loadLibrary("testjni");
        }
}

class testNativeTest {

        public static void main(String[] arg) {
                System.out.println("JAVA:call native") ;
                testNative.hello() ;
                testNative t = new testNative() ;
                System.out.println("JAVA:call native") ;
                String result = t.greeting("cj") ;
                System.out.println("JAVA:result from C:"+result) ;
        }
}
