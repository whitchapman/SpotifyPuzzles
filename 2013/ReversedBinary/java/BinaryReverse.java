import java.io.*;

public class BinaryReverse {

	public static void main(String[] args) {
		try {

			Reader reader = new InputStreamReader(System.in);
			BufferedReader buffer = new BufferedReader(reader);
			String s = buffer.readLine();
			buffer.close();
			int x = Integer.parseInt(s);

			//alternative way to read integer:
			//java.util.Scanner sc = new java.util.Scanner(System.in);
			//int x = sc.nextInt();

			String binary_x = Integer.toBinaryString(x);

			//could have used log function to calculate this, but wanted the string representation for output anyway.
			int num_bits = binary_x.length();

			int sum = 0;
			int value = (int) Math.pow(2.0, (double)num_bits);
			for (int i = 1; i <= x; i <<= 1) {
				value >>= 1;
				if ((x & i) > 0) {
					sum |= value;
				}
			}

			System.out.println(sum);

			//output as binary string:
			//String binary_sum = Integer.toBinaryString(sum);
			//int diff = num_bits - binary_sum.length();
			//while (diff > 0) {
			//	binary_sum = "0" + binary_sum;
			//	diff--;
			//}
			//System.out.println("in binary = " + binary_sum);

		} catch (IOException exn) {
			System.err.print("Exception reading from stdin:  ");
			exn.printStackTrace();
		} catch (NumberFormatException exn) {
			System.err.print("Exception with input, expected an integer N, 1 ≤ N ≤ 1000000000:  ");
			exn.printStackTrace();
		} catch (Exception exn) {
			System.err.print("Exception:  ");
			exn.printStackTrace();
		}
	}

}
