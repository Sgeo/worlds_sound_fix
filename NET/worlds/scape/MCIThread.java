package NET.worlds.scape;

import java.util.*;

public class MCIThread extends Thread {
    private Vector queue;


    public MCIThread() {
        this.queue = new Vector();
        this.start();
    }

    public void pushCommand(final MCISoundCommand c) {
        synchronized(this) {
            this.queue.addElement(c);
            c.onQueue(true);
            System.out.println("MCISoundCommand pushed");
        }
    }

    public void run() {
        while(true) {
            Vector cloned;
            synchronized(this) {
                cloned = (Vector)this.queue.clone();
                if(this.queue.size() > 0 || cloned.size() > 0) {
                    System.out.println("Some MCISoundCommands in the queue");
                }
                this.queue.clear();
                if(this.queue.size() > 0 || cloned.size() > 0) {
                    System.out.println("Still some MCISoundCommands in the queue");
                }
            }
            for(int i = 0; i < cloned.size(); i++) {
                System.out.println("Running an MCISoundCommand");
                final MCISoundCommand command = (MCISoundCommand)cloned.elementAt(i);
                command.onQueue(false);
                command.run();
            }
        }
    }

}
