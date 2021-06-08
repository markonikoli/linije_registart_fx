package application.util;

public class LineData {
	
	
	private String _pocetno_stajaliste = "";
	private String _krajnje_stajaliste = "";
	
	
	public LineData(String pocetno_stajaliste, String krajnje_stajaliste) {
		_pocetno_stajaliste = pocetno_stajaliste;
		_krajnje_stajaliste = krajnje_stajaliste;
	}


	public String get_pocetno_stajaliste() {
		return _pocetno_stajaliste;
	}


	public String get_krajnje_stajaliste() {
		return _krajnje_stajaliste;
	}


	@Override
	public String toString() {
		return _pocetno_stajaliste;
	}
	
	

}
