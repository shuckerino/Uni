import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

import com.refactor.Board;
import com.refactor.IO_Handler;
import com.refactor.Player;
import com.refactor.VierGewinnt;
import com.refactor.WinChecker;

public class VierGewinntTest {

    @Test
	public void testIsOverRow() throws Exception {
        assertOutcome("Spieler mit o hat gewonnen", 8,7,1, 1, 2, 2, 3, 3, 4);
	}

    @Test
    public void testIsOverStraight2() throws Exception {
        assertOutcome("Spieler mit o hat gewonnen", 8,7,2,3,3,5,4,4,5,5,5,6,4);
    }

    @Test
	public void testIsOverStraight1() throws Exception {
        assertOutcome("Spieler mit o hat gewonnen", 8,7,5,4,3,3,4,2,2,2,2,1,3);
	}

    @Test
	public void testUnentschieden() throws Exception {
		assertOutcome("Unentschieden!", 8,7,1,2,1,2,1,2,2,1,2,1,2,1,1,2,3,4,3,4,3,4,4,3,4,3,4,3,3,4,5,6,5,
                6,5,6,6,5,6,5,6,5,5,6,7,8,7,8,7,8,8,7,8,7,8,7,7,8);
	}

    @Test
    public void testIsOverColum() throws Exception {
        assertOutcome("Spieler mit o hat gewonnen", 8,7,6,5,5,6,5,6,5,6,5);
    }

    private void assertOutcome(String expectedOutcome, int width, int height, int... choices) {
        Player p1 = new Player("x", 'o');
        Player p2 = new Player("y", '+');
        Board gameBoard = new Board(width, height);

        final StringBuilder sb = new StringBuilder();
        for (int choice: choices) {
            sb.append(choice);
            sb.append("\n");
        }
        final InputStream in = new ByteArrayInputStream(sb.toString().getBytes());
        final ByteArrayOutputStream out = new ByteArrayOutputStream();
        final ByteArrayOutputStream err = new ByteArrayOutputStream();
        IO_Handler io_Handler = new IO_Handler(in, new PrintStream(out), new PrintStream(err));
        WinChecker winChecker = new WinChecker();
        VierGewinnt game = new VierGewinnt(p1, p2, io_Handler, gameBoard, winChecker);
        game.play();
        final String output = out.toString();
        //System.out.println("Expected output" + expectedOutcome);
        assertTrue(output.contains(expectedOutcome), "Incorrect output: " + output);
    }

}
