Content.makeFrontInterface(800, 500);

// KNOBS

// dichiarazione knob 4997
const var forty = Content.getComponent("forty");
// dichiarazione knob rose
const var rose = Content.getComponent("rose");
// dichiarazione knob mars
const var mars = Content.getComponent("MARS");
// dichiarazione button 
const var btnLink = Content.getComponent("Link");

// FX

// dichiarazione fx 4997 
const var phase = Synth.getEffect("Phase FX1");
const var newEffect = Synth.getEffect("Script FX1");
// dichiarazione fx d rose
const var reverb = Synth.getEffect("Simple Reverb1");
const var delay = Synth.getEffect("Delay1");
// dichiarazione fx ed mars 
const var distortion = Synth.getEffect("Shape FX1");

// function LINK

const var knobs = [forty, rose, mars];
reg i;

// Applica i valori al gruppo di effetti corrispondente a un knob
inline function applyKnob(idx, value)
{
    if (idx == 0) // forty
    {
        phase.setAttribute(phase.Mix, value / 2);
        newEffect.setAttribute(newEffect.granulax, value);
    }
    else if (idx == 1) // rose
    {
        reverb.setAttribute(reverb.WetLevel, value / 4);
        delay.setAttribute(delay.Mix, value / 2);
    }
    else if (idx == 2) // mars
    {
        distortion.setAttribute(distortion.Mix, value / 4);
    }
}function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{

	if (number == forty)
    {
        applyKnob(0, value);
        if (btnLink.getValue() == 1)
        {
            rose.setValue(value);
            mars.setValue(value);
            applyKnob(1, value);
            applyKnob(2, value);
        }
    }
    
    if (number == rose)
    {
        applyKnob(1, value);
        if (btnLink.getValue() == 1)
        {
            forty.setValue(value);
            mars.setValue(value);
            applyKnob(0, value);
            applyKnob(2, value);
        }
    }
    
    if (number == mars)
    {
        applyKnob(2, value);
        if (btnLink.getValue() == 1)
        {
            forty.setValue(value);
            rose.setValue(value);
            applyKnob(0, value);
            applyKnob(1, value);
        }
    }
	
}
 