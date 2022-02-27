// Setup
(
MIDIIn.connectAll;
MIDIFunc.trace(false);
SynthDef(\mico_sine, {|out=0, amp=0.125, freq=100|
    Out.ar(out, Pan2.ar(SinOsc.ar(freq)*amp * AmpComp.kr(freq), LFNoise2.kr(4).bipolar))
}).add;
)
// Register synths:
(
~sines=Array.newClear(4);
4.do{|index|
    var low = index + 1;
    ~sines[index] = Synth(\mico_sine);

    CC14.new(
        cc1:low, cc2:low+32, chan:0, fix:true, normalizeValues:true).func = {|val, chan, lowcc, highcc|
            "Encoder num %:".format(low).postln;
            val.postln;
            ~sines[index].set(\freq, val.linexp(0.0,1.0,80.0,1000.0))
        };
    }
)
