public class FunctionCall {

    public static int[] funct1 (char[] param1, int param2) {
	System.out.println ("Inside funct1");
    }

    public static void main (String[] args) {
	int val;

	System.out.println ("Inside main");

	funct1();

	System.out.println ("About to call funct2");

	val = funct2(8);

	System.out.println ("funct2 returned a value of " + val);

	System.out.println ("About to call funct2 again");

	val = funct2(-3);

	System.out.println ("funct2 returned a value of " + val);
    }

    private static Mytype.Insidetype funct2 (int param)
      throws ExceptionA, ExceptionB {
	System.out.println ("Inside funct2 with param " + param);
	return param * 2;
    }
}
