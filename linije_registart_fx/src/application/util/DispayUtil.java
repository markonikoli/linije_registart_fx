package application.util;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

public class DispayUtil {
	
	
	public static String toHexString(byte[] packet) {



        String digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                          "A", "B", "C", "D", "E", "F"};
        StringBuffer buffer = new StringBuffer();
        for (int i = 0; i < packet.length; i++) {
            int current = packet[i];
            if (current < 0)
                current = 256 + current;
            int high = 0;
            if (current >= 16)
                high = (int) Math.floor(current / 16);
            int low = current - high * 16;
            buffer.append(digits[high] + digits[low] + " ");
        }



        return buffer.toString();
    }
	
	public static String from_cirilic_to_latinic(String cirilic) {
		StringBuffer buffer = new StringBuffer();
		for(int i = 0; i < cirilic.length(); i++) {
			char current = cirilic.charAt(i);
			if(current == 'А') current = 'A';
			if(current == 'Б') current = 'B';
			if(current == 'В') current = 'V';
			if(current == 'Г') current = 'G';
			if(current == 'Д') current = 'D';
			if(current == 'Ђ') current = 'Đ';
			if(current == 'Е') current = 'E';
			if(current == 'Ж') current = 'Ž';
			if(current == 'З') current = 'Z';
			if(current == 'И') current = 'I';
			
			if(current == 'Ј') current = 'J';
			if(current == 'К') current = 'K';
			if(current == 'Л') current = 'L';
			if(current == 'Љ') current = 'L';
			if(current == 'М') current = 'M';
			if(current == 'Н') current = 'N';
			if(current == 'Њ') current = 'N';
			if(current == 'О') current = 'O';
			if(current == 'П') current = 'P';
			if(current == 'Р') current = 'R';
			
			if(current == 'С') current = 'S';
			if(current == 'Т') current = 'T';
			if(current == 'Ћ') current = 'Ć';
			if(current == 'У') current = 'U';
			if(current == 'Ф') current = 'F';
			if(current == 'Х') current = 'H';
			if(current == 'Ц') current = 'C';
			if(current == 'Ч') current = 'Č';
			if(current == 'Џ') current = 'D';
			if(current == 'Ш') current = 'Š';
			
			if(current == 'а') current = 'a';
			if(current == 'б') current = 'b';
			if(current == 'в') current = 'v';
			if(current == 'г') current = 'g';
			if(current == 'д') current = 'd';
			if(current == 'ђ') current = 'd';
			if(current == 'е') current = 'e';
			if(current == 'ж') current = 'ž';
			if(current == 'з') current = 'z';
			if(current == 'и') current = 'i';
			
			if(current == 'ј') current = 'j';
			if(current == 'к') current = 'k';
			if(current == 'л') current = 'l';
			if(current == 'љ') current = 'l';
			if(current == 'м') current = 'm';
			if(current == 'н') current = 'n';
			if(current == 'њ') current = 'n';
			if(current == 'о') current = 'o';
			if(current == 'п') current = 'p';
			if(current == 'р') current = 'r';
			
			if(current == 'с') current = 's';
			if(current == 'т') current = 't';
			if(current == 'ћ') current = 'ć';
			if(current == 'у') current = 'u';
			if(current == 'ф') current = 'f';
			if(current == 'х') current = 'h';
			if(current == 'ц') current = 'c';
			if(current == 'ч') current = 'č';
			if(current == 'џ') current = 'd';
			if(current == 'ш') current = 'š';
			
			
			buffer.append(current);
		}
		return buffer.toString();
	}
	
	
	public static byte[] from_cirilic_to_latinic_byte(String cirilic) throws IOException{
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		for(int i = 0; i < cirilic.length(); i++) {
			boolean added = false;
			char current = cirilic.charAt(i);
			if(current == 'А') {out.write(new byte[]{'A'}); added = true;}
			if(current == 'Б') {out.write(new byte[]{'B'}); added = true;}
			if(current == 'В') {out.write(new byte[]{'V'}); added = true;}
			if(current == 'Г') {out.write(new byte[]{'G'}); added = true;}
			if(current == 'Д') {out.write(new byte[]{'D'}); added = true;}
			if(current == 'Ђ') {out.write(new byte[]{0x1B}); added = true;}
			if(current == 'Е') {out.write(new byte[]{'E'}); added = true;}
			if(current == 'Ж') {out.write(new byte[]{0x17}); added = true;}
			if(current == 'З') {out.write(new byte[]{'Z'}); added = true;}
			if(current == 'И') {out.write(new byte[]{'I'}); added = true;}
			
			if(current == 'Ј') {out.write(new byte[]{'J'}); added = true;}
			if(current == 'К') {out.write(new byte[]{'K'}); added = true;}
			if(current == 'Л') {out.write(new byte[]{'L'}); added = true;}
			if(current == 'Љ') {out.write(new byte[]{'L','j'}); added = true;}
			if(current == 'М') {out.write(new byte[]{'M'}); added = true;}
			if(current == 'Н') {out.write(new byte[]{'N'}); added = true;}
			if(current == 'Њ') {out.write(new byte[]{'N','j'}); added = true;}
			if(current == 'О') {out.write(new byte[]{'O'}); added = true;}
			if(current == 'П') {out.write(new byte[]{'P'}); added = true;}
			if(current == 'Р') {out.write(new byte[]{'R'}); added = true;}
			
			if(current == 'С') {out.write(new byte[]{'S'}); added = true;}
			if(current == 'Т') {out.write(new byte[]{'T'}); added = true;}
			if(current == 'Ћ') {out.write(new byte[]{0x1D}); added = true;}
			if(current == 'У') {out.write(new byte[]{'U'}); added = true;}
			if(current == 'Ф') {out.write(new byte[]{'F'}); added = true;}
			if(current == 'Х') {out.write(new byte[]{'H'}); added = true;}
			if(current == 'Ц') {out.write(new byte[]{'C'}); added = true;}
			if(current == 'Ч') {out.write(new byte[]{0x1F}); added = true;}
			if(current == 'Џ') {out.write(new byte[]{'D',0x16}); added = true;}
			if(current == 'Ш') {out.write(new byte[]{0x19}); added = true;}
			
			if(current == 'а') {out.write(new byte[]{'a'}); added = true;}
			if(current == 'б') {out.write(new byte[]{'b'}); added = true;}
			if(current == 'в') {out.write(new byte[]{'v'}); added = true;}
			if(current == 'г') {out.write(new byte[]{'g'}); added = true;}
			if(current == 'д') {out.write(new byte[]{'d'}); added = true;}
			if(current == 'ђ') {out.write(new byte[]{0x1A}); added = true;}
			if(current == 'е') {out.write(new byte[]{'e'}); added = true;}
			if(current == 'ж') {out.write(new byte[]{0x16}); added = true;}
			if(current == 'з') {out.write(new byte[]{'z'}); added = true;}
			if(current == 'и') {out.write(new byte[]{'i'}); added = true;}
			
			if(current == 'ј') {out.write(new byte[]{'j'}); added = true;}
			if(current == 'к') {out.write(new byte[]{'k'}); added = true;}
			if(current == 'л') {out.write(new byte[]{'l'}); added = true;}
			if(current == 'љ') {out.write(new byte[]{'l','j'}); added = true;}
			if(current == 'м') {out.write(new byte[]{'m'}); added = true;}
			if(current == 'н') {out.write(new byte[]{'n'}); added = true;}
			if(current == 'њ') {out.write(new byte[]{'n','j'}); added = true;}
			if(current == 'о') {out.write(new byte[]{'o'}); added = true;}
			if(current == 'п') {out.write(new byte[]{'p'}); added = true;}
			if(current == 'р') {out.write(new byte[]{'r'}); added = true;}
			
			if(current == 'с') {out.write(new byte[]{'s'}); added = true;}
			if(current == 'т') {out.write(new byte[]{'t'}); added = true;}
			if(current == 'ћ') {out.write(new byte[]{0x1C}); added = true;}
			if(current == 'у') {out.write(new byte[]{'u'}); added = true;}
			if(current == 'ф') {out.write(new byte[]{'f'}); added = true;}
			if(current == 'х') {out.write(new byte[]{'h'}); added = true;}
			if(current == 'ц') {out.write(new byte[]{'c'}); added = true;}
			if(current == 'ч') {out.write(new byte[]{0x1E}); added = true;}
			if(current == 'џ') {out.write(new byte[]{'d', 0x16}); added = true;}
			if(current == 'ш') {out.write(new byte[]{0x18}); added = true;}
			
			if(!added) {
				out.write(new byte[]{(byte)current}); added = true;
			}
			
		}
		return out.toByteArray();
	}
	

	public static byte[] utf_to_ascii(String utf) throws Exception{
		boolean found_prvi = false;
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		byte[] utf_byte_array = utf.getBytes("UTF-8");
		for(int i = 0; i < utf_byte_array.length ; i++) {
			if (found_prvi) {
				found_prvi = false;
				continue;
			}
			if(utf_byte_array[i] == 0xD0 || utf_byte_array[i] == 0xD1 || utf_byte_array[i] == 0xC4 || utf_byte_array[i] == 0xC5) {
				if(utf_byte_array[i] == 0xD0 || utf_byte_array[i] == 0xD1) {
					//cirilica
					out.write(from_cirilic(utf_byte_array[i],utf_byte_array[i+1]));
				}else {
					//latinica
					out.write(from_latinica(utf_byte_array[i],utf_byte_array[i+1]));
				}
				found_prvi = true;
			}else {
				found_prvi = false;
				out.write(utf_byte_array[i]);
			}

		}
		
		return out.toByteArray();

	}
	
	
	private static byte[] from_cirilic(byte prvi, byte drugi) {
		if(prvi == 0xD0 & drugi == 0x90) return new byte[] {(byte)'A'};
		if(prvi == 0xD0 & drugi == 0xB0) return new byte[] {(byte)'a'};
		if(prvi == 0xD0 & drugi == 0x91) return new byte[] {(byte)'B'}; 
		if(prvi == 0xD0 & drugi == 0xB1) return new byte[] {(byte)'b'}; 
		if(prvi == 0xD0 & drugi == 0x92) return new byte[] {(byte)'V'}; 
		if(prvi == 0xD0 & drugi == 0xB2) return new byte[] {(byte)'v'}; 
		if(prvi == 0xD0 & drugi == 0x93) return new byte[] {(byte)'G'}; 
		if(prvi == 0xD0 & drugi == 0xB3) return new byte[] {(byte)'g'};
		if(prvi == 0xD0 & drugi == 0x94) return new byte[] {(byte)'D'};
		if(prvi == 0xD0 & drugi == 0xB4) return new byte[] {(byte)'d'}; 
		if(prvi == 0xD0 & drugi == 0x82) return new byte[] {0x1B}; //slovo Dj
		if(prvi == 0xD1 & drugi == 0x92) return new byte[] {0x1A}; //slovo dj
		if(prvi == 0xD0 & drugi == 0x95) return new byte[] {(byte)'E'}; 
		if(prvi == 0xD0 & drugi == 0xB5) return new byte[] {(byte)'e'}; 
		if(prvi == 0xD0 & drugi == 0x96) return new byte[] {0x17}; //slovo Z
		if(prvi == 0xD0 & drugi == 0xB6) return new byte[] {0x16}; //slovo z
		if(prvi == 0xD0 & drugi == 0x97) return new byte[] {(byte)'Z'}; 
		if(prvi == 0xD0 & drugi == 0xB7) return new byte[] {(byte)'z'}; 
		if(prvi == 0xD0 & drugi == 0x98) return new byte[] {(byte)'I'}; 
		if(prvi == 0xD0 & drugi == 0xB8) return new byte[] {(byte)'i'}; 
		if(prvi == 0xD0 & drugi == 0x88) return new byte[] {(byte)'J'}; 
		if(prvi == 0xD1 & drugi == 0x98) return new byte[] {(byte)'j'}; 
		if(prvi == 0xD0 & drugi == 0x9A) return new byte[] {(byte)'K'}; 
		if(prvi == 0xD0 & drugi == 0xBA) return new byte[] {(byte)'k'}; 
		if(prvi == 0xD0 & drugi == 0x9B) return new byte[] {(byte)'L'}; 
		if(prvi == 0xD0 & drugi == 0xBB) return new byte[] {(byte)'l'}; 
		if(prvi == 0xD0 & drugi == 0x89) return new byte[] {(byte)'L', (byte)'j'}; 
		if(prvi == 0xD1 & drugi == 0x99) return new byte[] {(byte)'l', (byte)'j'}; 
		if(prvi == 0xD0 & drugi == 0x9C) return new byte[] {(byte)'M'}; 
		if(prvi == 0xD0 & drugi == 0xBC) return new byte[] {(byte)'m'};
		if(prvi == 0xD0 & drugi == 0x9D) return new byte[] {(byte)'N'}; 
		if(prvi == 0xD0 & drugi == 0xBD) return new byte[] {(byte)'n'}; 
		if(prvi == 0xD0 & drugi == 0x8A) return new byte[] {(byte)'N', (byte)'j'}; 
		if(prvi == 0xD1 & drugi == 0x9A) return new byte[] {(byte)'n', (byte)'j'}; 
		if(prvi == 0xD0 & drugi == 0x9E) return new byte[] {(byte)'O'}; 
		if(prvi == 0xD0 & drugi == 0xBE) return new byte[] {(byte)'o'}; 
		if(prvi == 0xD0 & drugi == 0x9F) return new byte[] {(byte)'P'}; 
		if(prvi == 0xD0 & drugi == 0xBF) return new byte[] {(byte)'p'};
		if(prvi == 0xD0 & drugi == 0xA0) return new byte[] {(byte)'R'}; 
		if(prvi == 0xD1 & drugi == 0x80) return new byte[] {(byte)'r'};
		if(prvi == 0xD0 & drugi == 0xA1) return new byte[] {(byte)'S'}; 
		if(prvi == 0xD1 & drugi == 0x81) return new byte[] {(byte)'s'}; 
		if(prvi == 0xD0 & drugi == 0xA2) return new byte[] {(byte)'T'}; 
		if(prvi == 0xD1 & drugi == 0x82) return new byte[] {(byte)'t'}; 
		if(prvi == 0xD0 & drugi == 0x8B) return new byte[] {0x1D}; //Tj
		if(prvi == 0xD1 & drugi == 0x9B) return new byte[] {0x1C}; //tj
		if(prvi == 0xD0 & drugi == 0xA3) return new byte[] {(byte)'U'};
		if(prvi == 0xD1 & drugi == 0x83) return new byte[] {(byte)'u'}; 
		if(prvi == 0xD0 & drugi == 0xA4) return new byte[] {(byte)'F'}; 
		if(prvi == 0xD1 & drugi == 0x84) return new byte[] {(byte)'f'}; 
		if(prvi == 0xD0 & drugi == 0xA5) return new byte[] {(byte)'H'}; 
		if(prvi == 0xD1 & drugi == 0x85) return new byte[] {(byte)'h'}; 
		if(prvi == 0xD0 & drugi == 0xA6) return new byte[] {(byte)'C'}; 
		if(prvi == 0xD1 & drugi == 0x86) return new byte[] {(byte)'c'};
		if(prvi == 0xD0 & drugi == 0xA7) return new byte[] {0x1F}; //Ch
		if(prvi == 0xD1 & drugi == 0x87) return new byte[] {0x1E}; //Ch
		if(prvi == 0xD0 & drugi == 0x8F) return new byte[] {(byte)'D', (byte)'z'}; 
		if(prvi == 0xD1 & drugi == 0x9F) return new byte[] {(byte)'d', (byte)'z'};
		if(prvi == 0xD0 & drugi == 0xA8) return new byte[] {0x19}; //Sh
		if(prvi == 0xD1 & drugi == 0x88) return new byte[] {0x18}; //sh
		
		return new byte[] {prvi, drugi};

	}
	
	private static byte[] from_latinica(byte prvi, byte drugi) {
		if(prvi == 0xC4 & drugi == 0x90) return new byte[] {0x1B}; //slovo Dj
		if(prvi == 0xC4 & drugi == 0x91) return new byte[] {0x1A}; //slovo dj
		if(prvi == 0xC5 & drugi == 0xBD) return new byte[] {0x17}; //slovo Z
		if(prvi == 0xC5 & drugi == 0xBE) return new byte[] {0x16}; //slovo z
		if(prvi == 0xC4 & drugi == 0x86) return new byte[] {0x1D}; //Tj
		if(prvi == 0xC4 & drugi == 0x87) return new byte[] {0x1C}; //tj
		if(prvi == 0xC4 & drugi == 0x8C) return new byte[] {0x1F}; //Ch
		if(prvi == 0xC4 & drugi == 0x8D) return new byte[] {0x1E}; //Ch
		if(prvi == 0xC5 & drugi == 0xA0) return new byte[] {0x19}; //Sh
		if(prvi == 0xC5 & drugi == 0xA1) return new byte[] {0x18}; //sh
		return new byte[] {prvi, drugi};
	}
	
	
	
	
	
	
//
//
//	private char utf_cirilica_to_ascii(char[] utf_cirilic_char) {
//		if ( utf_cirilic_char[0] == 0xC4 ||
//				utf_cirilic_char[0] == 0xC5 )
//		{
//
//			if ( utf_cirilic_char[1] == 0x86 )
//			{
//				return 0x1D;
//
//			}
//			else if ( utf_cirilic_char[1] == 0x87 )
//			{
//				return 0x1C;
//			}
//			else if ( utf_cirilic_char[1] == 0x8C )
//			{
//				return 0x1F;
//			}
//			else if ( utf_cirilic_char[1] == 0x8D )
//			{
//				return 0x1E;
//			}
//			else if ( utf_cirilic_char[1] == 0x90 )
//			{
//				return 0x1B;
//			}
//			else if ( utf_cirilic_char[1] == 0x91 )
//			{
//				return 0x1A;
//			}
//			else if ( utf_cirilic_char[1] == 0xA0 )
//			{
//				return 0x19;
//			}
//			else if ( utf_cirilic_char[1] == 0xA1 )
//			{
//				return 0x18;
//			}
//			else if ( utf_cirilic_char[1] == 0xBD )
//			{
//				return 0x17;
//			}
//			else if ( utf_cirilic_char[1] == 0xBE )
//			{
//				return 0x16;
//			}
//		}
//
//
//	}
	
	
	public static void main(String[] args) throws Exception{
		byte[] bytes_cirilica = "АаБбВвГгДдЂђЕеЖжЗзИиЈјКкЛлЉљМмНнЊњОоПпРрСсТтЋћУуФфХхЦцЧчЏџШш0123456789 ".getBytes("UTF-8");
		byte[] bytes_laticnica = "ĐđŽžĆćČčŠš".getBytes("UTF-8");
		for(int i = 0; i< bytes_cirilica.length;i++) {
			System.out.println(Integer.toHexString((int) bytes_cirilica[i]));
		}
		
		System.out.println("bytes_cirilica = " + toHexString(bytes_cirilica));
		System.out.println("bytes_laticnica = " + toHexString(bytes_laticnica));
		
		
		System.out.println(toHexString(from_cirilic_to_latinic_byte("АаБбВвГгДдЂђЕеЖжЗзИиЈјКкЛлЉљМмНнЊњОоПпРрСсТтЋћУуФфХхЦцЧчЏџШш0123456789 ")));
		
	}
}
