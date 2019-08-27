// A couple of global variables
var start, stop, stopwatchBox;
var starttime ;
var status ; // 0=init, 1=working, 2=paused
var offsettime ;

// Grab the necessary elements from the DOM
start = document.getElementById("start");
stop = document.getElementById("stop");
stopwatchBox = document.getElementById("stopwatch-box");
starttime = new Date() ;
offsettime = 0 ;
savedelapsed = 0 ;
status = 0 ;

// Add event listeners to both buttons
start.addEventListener("click", function() {
  stopwatch("start");
});

stop.addEventListener("click", function() {
  stopwatch("stop");
});

// Define a timer ID for the setInterval function
timerId = null;

// Create the stopwatch
function stopwatch(command) {
  var hours = 0,
    minutes = 0,
    seconds = 0,
    milli = 0,
    display;

  function makeZeroPad(number, len) {
    // len:  the length of output we want to make number
    var outnumber=String(number) ;
    if ( outnumber.length  < len ) {
      for (i=0; i<(len-String(number).length); i++)
        outnumber = "0"+outnumber ;
    }
    return outnumber;
  }

  if (command === "start") {
    if (timerId!=null) {
      if (status==1) { // working..
        stopwatch("stop");  // pause!
      }
      return ;  // on working....
    }
    if (status==0) {  // init
      status=1 ;
      offsettime=0 ;
    } else if (status==2) { // paused
      // resume
      status=1 ;
    } 
    starttime = new Date() ;
    timerId = setInterval(function() {
      nowtime = new Date() ;
      elapsed = nowtime - starttime ; // ms
      elapsed += offsettime ;   // for resume.
      savedelapsed = elapsed ;  // for save.

      hours = Math.floor(elapsed / (3600*1000)) ;
      remain = elapsed - hours * (3600*1000) ;
      minutes =  Math.floor(remain / (60*1000)) ;
      remain = remain - minutes * (60*1000) ;
      seconds =  Math.floor(remain / (1*1000)) ;
      milli = remain - seconds*(1*1000) ;

      display =
        makeZeroPad(hours, 2) +
        ":" +
        makeZeroPad(minutes, 2) +
        ":" +
        makeZeroPad(seconds, 2) +
        ":" +
        makeZeroPad(milli, 3) ;
      stopwatchBox.innerHTML = display;
//      console.log(display);
    }, 1);
  } else if (command === "stop") {
    if (timerId)
      clearInterval(timerId);
    timerId=null ;
    if (status==0 || status==2) {
      status=0 ;
      offsettime=0 ;
      stopwatchBox.innerHTML = "00:00:00.000" ;
    } else if (status==1) {
      // paused
      status=2 ;
      offsettime = savedelapsed ;
    }    
  }
}