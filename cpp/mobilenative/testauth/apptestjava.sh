#!/bin/sh
javac -d . testNative.java
java -cp . com.my.app.testNativeTest

