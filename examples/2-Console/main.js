/*  An example showing how to
    interact with the console

    2014, Johnathan Corkery
*/

// First, we want to create our window on the system.
window = sandboxe.display.create("Console Example");
sandboxe.display.setMain(window);








// Since we are only going to be working in the console,
// lets have the Entity switch to the console right away for us.
// This can be done manually by pressing Shift + TAB at any time.
// While on the console, Shift+TAB will bring you back to the scene.
// Note that brining up the console does not stop or pause the scene.
sandboxe.console.show(true);

// Lets output a simple message: "Greetings"
sandboxe.console.info("Greetings");


// The Info() function informs Dynacoe to print output to the console. 
// To mark the end of the line, the message must end in a Console::End.
sandboxe.console.info(" and Salutations!\n"); // now the line reads: Greetings and Salutations!



// we can also chain pipe commands indefinitely:
sandboxe.console.info("How are you?\n" +
                       "What is new?\n");
// For readability, usually lines of output are given their own line
// when piping multiple lines under one call.


// there are other line types to try:
sandboxe.console.info   ("This is system info.\n"); 
sandboxe.console.warning("This is a warning. Usually for things " +
                         "that are non-fatal.\n");
sandboxe.console.error  ("This is an error. Usually for things " +
                         "that aren't recoverable.\n");

