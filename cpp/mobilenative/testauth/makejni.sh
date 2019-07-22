#!/bin/sh
javac -d . testNative.java
javah -cp . com.my.app.testNative
