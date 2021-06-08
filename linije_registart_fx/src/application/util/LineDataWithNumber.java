package application.util;

public class LineDataWithNumber extends LineData{
	
	private int _line_number = -1;
	private String _sub_line = "";
	
	public LineDataWithNumber(int line_number, String sub_line, String pocetno_stajaliste, String krajnje_stajaliste) {
		super(pocetno_stajaliste, krajnje_stajaliste);
		_line_number = line_number;
		_sub_line = sub_line;
	}

	public int get_line_number() {
		return _line_number;
	}

	public String get_sub_line() {
		return _sub_line;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		if(obj != null) {
			String line_subline = obj.toString();
			if(obj instanceof LineDataWithNumber) {
				LineDataWithNumber to_compare_with = (LineDataWithNumber)obj;
				line_subline = to_compare_with.get_line_number() + to_compare_with.get_sub_line();
			}
			String this_line_subline = get_line_number() + get_sub_line();
			return this_line_subline.equals(line_subline);
		}else {
			return false;
		}
	}

	@Override
	public String toString() {
		return _line_number + ":" +  _sub_line + ":"
				+ super.get_pocetno_stajaliste() + ":" + super.get_krajnje_stajaliste() ;
	}
	
	
	

}
