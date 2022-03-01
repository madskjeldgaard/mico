/*

Control 4 sine waves using the Mico.

Needs the CC14 quark to work:
Quarks.install("CC14");

*/
// Setup
(
s.waitForBoot{

    // Connect midi device
    MIDIIn.connectAll;
    s.sync;
    // MIDIFunc.trace(true);
    // MIDIFunc.trace(false);

    // Add SynthDef
    SynthDef(\mico_sine, {|out=0, amp=0.125, freq=100|
        Out.ar(out, Pan2.ar(SinOsc.ar(freq.lag)*amp * AmpComp.kr(freq), LFNoise2.kr(4).bipolar))
    }).add;

    // Make sines
    s.sync;
    ~sines=Array.newClear(4);

    // Register callback for each encoder
    4.do{|index|
        var low = index + 1;
        ~sines[index] = Synth(\mico_sine);

        CC14.new(
            cc1:low,
            cc2:low+32,
            chan:1,
            fix:true,
            normalizeValues:true
        ).func = {|val, chan, lowcc, highcc|
            "Encoder num %:".format(low).postln;
            val.postln;
            ~sines[index].set(\freq, val.linexp(0.0,1.0,80.0,1000.0))
        };
    }
}
)
