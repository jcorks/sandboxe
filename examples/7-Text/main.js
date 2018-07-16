/*  A Basic example that shows how to work with text rendering
    2014, Johnathan Corkery
 */


// First, we want to create our window on the system.
window = sandboxe.display.create("Text Example");
sandboxe.display.setMain(window);

// We're going to work with a single object this time.
// Lets prepare our text renderer.
object = sandboxe.entity.create();

// Text is rendered is using the text2d component
object.text = object.add('text2d');

// The font needs to be loaded. By default, sandboxe can open TTF and OTF fonts.
object.text.font = sandboxe.assets.load('ttf', 'monospace.ttf');

// We can always set the size as well
object.text.fontSize = 24;


object.text.text = 'Try typing!';
object.text.spacingMode = sandboxe.component.text2d.spacingMode.monospace;

var text = "";
object.onStep = function() {
    // This controls when to add additional characters to 
    // this displayed string. GetLastUnicode() is a nifty function for 
    // retrieving the last character the user typed. This takes into 
    // account Shift.
    if (character = sandboxe.input.getLastUnicode()) {
        if (character == 8) { // backspace
            text = text.substr(0, text.length-1);
        } else {
            text += String.fromCharCode(character);
        }
        object.text.text =  text + '|';
    }
    

    
    // Text rendering with Dynacoe gives you a few options to 
    // display character spacings. 'Kerned' text draws the text 
    // using the natural spacing determined by the font. This is the 
    // most aesthetically pleasing, but is more work to predict 
    // how much real estate the text will require.
    if (sandboxe.input.isPressed(sandboxe.key_right)) {
        object.text.spacingMode = sandboxe.component.text2d.spacingMode.kerned;
        sandboxe.console.info("Changed spacing mode to: Kerned\n");
    } 

    // 'Bitmap' text will draw the text with spacing determined from 
    // just the visual. Rarely useful, but you never know!
    if (sandboxe.input.isPressed(sandboxe.key_left)) {
        object.text.spacingMode = sandboxe.component.text2d.spacingMode.bitmap;
        sandboxe.console.info("Changed spacing mode to: Bitmap\n");
    } 

    // 'Monospace' text will draw the text with the same spacing 
    // regardless of the character. This is very useful because, in this mode, 
    // you can predict the space usage of the text to be drawn just by 
    // the character count.
    if (sandboxe.input.isPressed(sandboxe.key_up)) {
        object.text.spacingMode = sandboxe.component.text2d.spacingMode.monospace;
        sandboxe.console.info("Changed spacing mode to: Monospace\n");
    } 
    
}


sandboxe.engine.setRoot(object);
