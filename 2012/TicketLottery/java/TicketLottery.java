import java.io.*;
import java.util.*;

class Combination {
	private int n;
	private int k;

	public Combination(int n, int k) {
		this.n = n;
		this.k = k;
	}

	public void print() {
		System.out.println("C(" + this.n + ", " + this.k + ")");
	}

	public boolean process(List<Integer> virtual_nums, List<Integer> virtual_dens) {

		//return false to indicate the value of this combination is zero
		if (this.n < this.k) {
			return false;
		}

		//the value of this combination is one -- no need to add any factorials
		if ((this.n == this.k) || (this.k == 0)) {
			return true;
		}

		//add n! to the numerator
		if (this.n > 1) {
			virtual_nums.add(this.n);
		}

		//add k! to the denominator
		if (this.k > 1) {
			virtual_dens.add(this.k);
		}

		//add n-k! to the denominator
		if (this.n - this.k > 1) {
			virtual_dens.add(this.n - this.k);
		}

		return true;
	}
}

class Factorials {

	public static double divide(int num, int den) {
		double result = 1.0;

		if (num < den) {

			for (int i = num+1; i <= den; i++) {
				result /= (double)i;
			}

		} else if (num > den) {

			for (int i = den+1; i <= num; i++) {
				result *= (double)i;
			}

		}

		return result;
	}
}

class CombinationOperator {
	private boolean is_zero;
	private List<Integer> nums;
	private List<Integer> dens;

	public CombinationOperator() {
		is_zero = false;
		this.nums = new ArrayList<>();
		this.dens = new ArrayList<>();
	}

	public void reset() {
		is_zero = false;
		this.nums.clear();
		this.dens.clear();		
	}

	public void print() {
		System.out.println("");
		for (int i=0; i < this.nums.size(); i++) {
			System.out.print(this.nums.get(i) + "! ");
		}
		System.out.println("");

		System.out.println("--------------");

		for (int i=0; i < this.dens.size(); i++) {
			System.out.print(this.dens.get(i) + "! ");
		}
		System.out.println("");
		System.out.println("");
	}

	public void multiply(Combination c) {
		if (!c.process(this.nums, this.dens)) {
			is_zero = true;
		}
	}

	public void divide(Combination c) {
		if (!c.process(this.dens, this.nums)) {
			is_zero = true;
		}
	}

	public double value() {

		if (this.is_zero) {
			return 0.0;
		}

		Collections.sort(this.nums);
		Collections.sort(this.dens);

		//minimize the number of mathematical operations by using factorial division to cancel out as much as possible

		double result = 1.0;

		int i = this.nums.size() - 1;
		int j = this.dens.size() - 1;

		while ((i >= 0) || (j >= 0)) {

			int num = 1;
			if (i >= 0) {
				num = this.nums.get(i);
			}

			int den = 1;
			if (j >= 0) {
				den = this.dens.get(j);
			}

			result *= Factorials.divide(num, den);

			i--;
			j--;
		}

		return result;
	}
}

public class TicketLottery {

	private static double calculate(CombinationOperator co, int m, int n, int p, int x) {

		co.reset();

		//the probability is calculated by dividing the number of possibilities
		//of winning combinations over the total number of combinations.

		//number of combinations from group choosing x winners
		Combination c1 = new Combination(p, x);
		co.multiply(c1);

		//number of combinations from non-group choosing remaining number of slots
		Combination c2 = new Combination(m-p, n-x);
		co.multiply(c2);

		//total number of combinations
		Combination c3 = new Combination(m, n);
		co.divide(c3);

		return co.value();
	}

	public static void main(String[] args) {
		try {

			Reader reader = new InputStreamReader(System.in);
			BufferedReader buffer = new BufferedReader(reader);
			String line = buffer.readLine();
			buffer.close();

			String[] arr = line.split(" ", 4);

			int m = Integer.parseInt(arr[0]);
			int n = Integer.parseInt(arr[1]);
			int t = Integer.parseInt(arr[2]);
			int p = Integer.parseInt(arr[3]);

			int min = 1;
			while (min * t < p) {
				min++;
			}

			int max = p;
			if (n < p) {
				max = n;
			}

			CombinationOperator co = new CombinationOperator();

			double sum = 0.0;
			for (int x=min; x <= max; x++) {

				double result = calculate(co, m, n, p, x);
				//System.out.println("P(" + x + ") = " + result + "\n");

				sum += result;
			}

			System.out.println(String.format("%.10f", sum));

		} catch (IOException exn) {
			System.err.print("Exception reading from stdin:  ");
			exn.printStackTrace();
		} catch (Exception exn) {
			System.err.print("Exception:  ");
			exn.printStackTrace();
		}
	}
}
