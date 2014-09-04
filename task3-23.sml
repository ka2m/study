(* N - ������������� �������� *)
load "Math";
fun y N =
  let
    val rN = real N
	
    (* ���������� ���� (�����): ������� i-�� ���������
     * �������� � j-�� ��������� ���������� slag *)
    fun jIter (i, j, slag) =
      if j > rN then slag
      else jIter (i, j + 1.0, slag + (((Math.exp)^i) / Math.lg (j)));

    (* ������� ���� (�����):
     * ���������� i-�� ���������� (��� i<=N) � ���������� rez *)
    fun iIter (i, rez) =
      if i > rN then rez
      else iIter (i + 1.0, rez + jIter (i, 2.0, 1.0));
  in
    (* ����������� ���� �� i (������������) �� 1.0  *)
    iIter (1.0, 0.0)
  end;