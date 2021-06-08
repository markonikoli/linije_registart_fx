package application;

import java.awt.Insets;
import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

import application.util.DispayUtil;
import application.util.InputFileReader;
import application.util.LineDataWithNumber;
import application.util.LineWithNumberCollection;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListCell;
import javafx.scene.image.ImageView;
import javafx.scene.control.Label;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.text.TextAlignment;
import javafx.util.StringConverter;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;

public class MainUIController extends AbstractController implements Initializable{
	
	@FXML private AnchorPane root_pane;
//	@FXML private Button osvezi_btn;
	@FXML private Button prihvati_btn;
	@FXML private Button jedan_btn; 
	@FXML private Button dva_btn;
	@FXML private Button tri_btn;
	@FXML private Button cetiri_btn;
	@FXML private Button pet_btn;
	@FXML private Button sest_btn;
	@FXML private Button sedam_btn;
	@FXML private Button osam_btn;
	@FXML private Button devet_btn;
	@FXML private Button nula_btn;
	@FXML private Button back_space_btn;
	
	@FXML private Button izmeni_smer_btn;
	@FXML private Button direction_btn;
//	@FXML private ChoiceBox<String> podlinija_cbx;
//	@FXML private ChoiceBox<String> smer_cbx;
	@FXML private ComboBox<LineDataWithNumber> line_number_selectin_cmb;
//	@FXML private Label izaberi_podliniju_lbl;
//	@FXML private Label izaberi_smer_lbl;
	@FXML private Label disp_line_title_lbl;
	@FXML private Label veliki_broj_linije_lbl;
	@FXML private Label disp_line_num_lbl;
	@FXML private Label disp_line_text_up;
	@FXML private Label disp_line_text_down;
	
	@FXML private Button goToIzaberiLinijuVeliko_btn;
	
	
	@FXML private ImageView light_blue_background;
	
	
	private String _display_smer_A = "";
	private String _display_smer_B = "";
	
	private LineWithNumberCollection _line_data = null;
	
	private String _current_display = "";
	
	private LineDataWithNumber _selected_line = null;
	
	@FXML private Label linija_od_gore_lbl;
	@FXML private Label linija_do_gore_lbl;
	@FXML private Label linija_od_dole_lbl;
	@FXML private Label linija_do_dole_lbl;
	
	@FXML private Button goToIzaberiLiniju_btn;
	
	@FXML private Button odustani_btn;
	
	@FXML private Label potvrdi_gornja_lbl;
	@FXML private Label potvrdi_srednja_lbl;
	@FXML private Label potvrdi_donja_lbl;
	@FXML private Label potvrdi_linija_lbl;
	
	
	private void display_init_screen() {
		root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_up.gif')");
		linija_od_gore_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_gore_lbl.setAlignment(Pos.CENTER_LEFT);
		linija_od_dole_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_dole_lbl.setAlignment(Pos.CENTER_LEFT);
		potvrdi_gornja_lbl.setAlignment(Pos.CENTER);
		potvrdi_srednja_lbl.setAlignment(Pos.CENTER_RIGHT);
		potvrdi_donja_lbl.setAlignment(Pos.CENTER);
		potvrdi_linija_lbl.setAlignment(Pos.CENTER_LEFT);
		light_blue_background.setVisible(false);
		disp_line_num_lbl.setVisible(false);
		disp_line_text_up.setVisible(false);
		disp_line_text_down.setVisible(false);
		prihvati_btn.setVisible(false);
		jedan_btn.setVisible(false);
		dva_btn.setVisible(false);
		tri_btn.setVisible(false);
		cetiri_btn.setVisible(false);
		pet_btn.setVisible(false);
		sest_btn.setVisible(false);
		sedam_btn.setVisible(false);
		osam_btn.setVisible(false);
		devet_btn.setVisible(false);
		nula_btn.setVisible(false);
		back_space_btn.setVisible(false);
		line_number_selectin_cmb.setVisible(false);
		izmeni_smer_btn.setVisible(false);
		direction_btn.setVisible(false);
		disp_line_title_lbl.setVisible(false);
		veliki_broj_linije_lbl.setVisible(false);
		linija_od_gore_lbl.setVisible(false);
		linija_do_gore_lbl.setVisible(false);
		linija_od_dole_lbl.setVisible(false);
		linija_do_dole_lbl.setVisible(false);
		goToIzaberiLiniju_btn.setVisible(false);
		odustani_btn.setVisible(false);
		potvrdi_gornja_lbl.setVisible(false);
		potvrdi_srednja_lbl.setVisible(false);
		potvrdi_donja_lbl.setVisible(false);
		potvrdi_linija_lbl.setVisible(false);
		goToIzaberiLinijuVeliko_btn.setVisible(true);
	}
	
	private void display_home_screen() {
		root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_up.gif')");
		linija_od_gore_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_gore_lbl.setAlignment(Pos.CENTER_LEFT);
		linija_od_dole_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_dole_lbl.setAlignment(Pos.CENTER_LEFT);
		light_blue_background.setVisible(false);
		disp_line_num_lbl.setVisible(false);
		disp_line_text_up.setVisible(false);
		disp_line_text_down.setVisible(false);
		prihvati_btn.setVisible(false);
		jedan_btn.setVisible(false);
		dva_btn.setVisible(false);
		tri_btn.setVisible(false);
		cetiri_btn.setVisible(false);
		pet_btn.setVisible(false);
		sest_btn.setVisible(false);
		sedam_btn.setVisible(false);
		osam_btn.setVisible(false);
		devet_btn.setVisible(false);
		nula_btn.setVisible(false);
		back_space_btn.setVisible(false);
		line_number_selectin_cmb.setVisible(false);
		izmeni_smer_btn.setVisible(true);
		direction_btn.setVisible(true);
		disp_line_title_lbl.setVisible(true);
		veliki_broj_linije_lbl.setVisible(true);
		linija_od_gore_lbl.setVisible(true);
		linija_do_gore_lbl.setVisible(true);
		linija_od_dole_lbl.setVisible(true);
		linija_do_dole_lbl.setVisible(true);
		potvrdi_gornja_lbl.setVisible(false);
		potvrdi_srednja_lbl.setVisible(false);
		potvrdi_donja_lbl.setVisible(false);
		potvrdi_linija_lbl.setVisible(false);
		goToIzaberiLiniju_btn.setVisible(true);
		odustani_btn.setVisible(false);
		goToIzaberiLinijuVeliko_btn.setVisible(false);
	}
	
	
	private void display_selection_screen() {
		root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_right.gif')");
		disp_line_num_lbl.setAlignment(Pos.CENTER_LEFT);
		disp_line_text_up.setAlignment(Pos.CENTER_RIGHT);
		disp_line_text_down.setAlignment(Pos.CENTER_RIGHT);
		veliki_broj_linije_lbl.setAlignment(Pos.CENTER);
		light_blue_background.setVisible(true);
		disp_line_num_lbl.setVisible(true);
		disp_line_text_up.setVisible(true);
		disp_line_text_down.setVisible(true);
		prihvati_btn.setVisible(false);
		jedan_btn.setVisible(true);
		dva_btn.setVisible(true);
		tri_btn.setVisible(true);
		cetiri_btn.setVisible(true);
		pet_btn.setVisible(true);
		sest_btn.setVisible(true);
		sedam_btn.setVisible(true);
		osam_btn.setVisible(true);
		devet_btn.setVisible(true);
		nula_btn.setVisible(true);
		back_space_btn.setVisible(true);
		line_number_selectin_cmb.setVisible(true);
		izmeni_smer_btn.setVisible(false);
		direction_btn.setVisible(false);
		disp_line_title_lbl.setVisible(false);
		veliki_broj_linije_lbl.setVisible(false);
		linija_od_gore_lbl.setVisible(false);
		linija_do_gore_lbl.setVisible(false);
		linija_od_dole_lbl.setVisible(false);
		linija_do_dole_lbl.setVisible(false);
		goToIzaberiLiniju_btn.setVisible(false);
		potvrdi_gornja_lbl.setVisible(false);
		potvrdi_srednja_lbl.setVisible(false);
		potvrdi_donja_lbl.setVisible(false);
		potvrdi_linija_lbl.setVisible(false);
		odustani_btn.setVisible(true);
		goToIzaberiLinijuVeliko_btn.setVisible(false);
	}
	
    @Override
    public void initialize(URL location, ResourceBundle resources) {
    	
    	_line_data = (LineWithNumberCollection)InputFileReader.getCollection();
    	
    	
    	init_main_cmb();
    	//initSelectionHandler(jedinice_cbx);
//    	setSelectionListeners();
    	display_init_screen();
    }
	
	
	public void handlePrihvati() {
		
		if(_selected_line != null) {
			_current_display = "Линија: " + getSelectedLine() + " " + _selected_line.get_pocetno_stajaliste();
			_display_smer_A = "Линија: " + getSelectedLine() + " " + _selected_line.get_pocetno_stajaliste();
			_display_smer_B = "Линија: " + getSelectedLine() + " " + _selected_line.get_krajnje_stajaliste();
			
			String[] splt_od = _selected_line.get_pocetno_stajaliste().split(" ",0);
			linija_od_gore_lbl.setText(splt_od[0]);
			if(splt_od.length > 1) {
				linija_od_dole_lbl.setText(splt_od[1]);
			}else {
				linija_od_dole_lbl.setText("");
			}
			veliki_broj_linije_lbl.setText(getSelectedLine());
			
			String[] splt_do = _selected_line.get_krajnje_stajaliste().split(" ",0);
			linija_do_gore_lbl.setText(splt_do[0]);
			if(splt_do.length > 1) {
				linija_do_dole_lbl.setText(splt_do[1]);
			}else {
				linija_do_dole_lbl.setText("");
			}
			
		}

		System.out.println("prihvati akcija");
		send_to_displays();
		reset();
	}
	
	public void goToIzaberiLiniju() {
		display_selection_screen();
	}
	
	
	public void handleOdustani() {
		reset_combo_box();
		display_home_screen();
		disp_line_num_lbl.setText("");
		disp_line_text_up.setText("");
		disp_line_text_down.setText("");
	}
	
	public void handleComboBoxSelection() {
		System.out.println("handleComboBoxSelection akcija, selected " + line_number_selectin_cmb.getValue());
		LineDataWithNumber new_selection_line = line_number_selectin_cmb.getValue();
		if(new_selection_line == null) {
			return;
		}else {
			_selected_line = new_selection_line;
		}
		
		//if(_selected_line != null) {
		


			disp_line_num_lbl.setText(_selected_line.get_line_number() + _selected_line.get_sub_line());
			disp_line_text_up.setText(_selected_line.get_pocetno_stajaliste());
			disp_line_text_down.setText(_selected_line.get_krajnje_stajaliste());
			
			potvrdi_gornja_lbl.setVisible(true);
			potvrdi_srednja_lbl.setVisible(true);
			potvrdi_donja_lbl.setVisible(true);
			potvrdi_linija_lbl.setText(_selected_line.get_line_number() + _selected_line.get_sub_line());
			potvrdi_linija_lbl.setVisible(true);
			prihvati_btn.setVisible(true);
//			_current_display = "Линија: " + getSelectedLine() + " " + _selected_line.get_pocetno_stajaliste();
//			dispay_lbl.setText(_current_display);
//			_display_smer_A = "Линија: " + getSelectedLine() + " " + _selected_line.get_pocetno_stajaliste();
//			_display_smer_B = "Линија: " + getSelectedLine() + " " + _selected_line.get_krajnje_stajaliste();
//			
//			String[] splt_od = _selected_line.get_pocetno_stajaliste().split(" ",1);
//			linija_od_gore_lbl.setText(splt_od[0]);
//			if(splt_od.length > 1) {
//				linija_od_dole_lbl.setText(splt_od[1]);
//			}else {
//				linija_od_dole_lbl.setText("");
//			}
//			dispay_lbl.setText(getSelectedLine());
//			
//			String[] splt_do = _selected_line.get_krajnje_stajaliste().split(" ",1);
//			linija_do_gore_lbl.setText(splt_do[0]);
//			if(splt_od.length > 1) {
//				linija_do_dole_lbl.setText(splt_do[1]);
//			}else {
//				linija_do_dole_lbl.setText("");
//			}
			
			reset_combo_box();
		//}
//		set_smer();
		
	}
	

	public void handleOsvezi() {
		System.out.println("ozvezi akcija");
		set_mode_to_auto();
		reset();
		System.exit(0);
	}
	
	public void handleIzmeniSmer() {
		System.out.println("izmeni smer akcija: _current_display = " + _current_display + ",\n _display_smer_A = " + _display_smer_A + "\n _display_smer_B = " + _display_smer_B);
		if(_current_display.equals(_display_smer_A)) {
			_current_display = _display_smer_B;
				
		}
		else {
			_current_display = _display_smer_A;
			
		}
		String swap_buffer = linija_do_gore_lbl.getText();
		linija_do_gore_lbl.setText(linija_od_gore_lbl.getText());
		linija_od_gore_lbl.setText(swap_buffer);
		
		swap_buffer = linija_do_dole_lbl.getText();
		linija_do_dole_lbl.setText(linija_od_dole_lbl.getText());
		linija_od_dole_lbl.setText(swap_buffer);
		
		
		
		
		send_to_displays();
	}
	
	private boolean is_number(String num) {

		try {
			Integer.parseInt(num);
			return true;
		}catch(Throwable e) {
			return false;
		}
	}

	public void handleNula() {
		String editor_text = line_number_selectin_cmb.getEditor().getText();
		if(is_number(editor_text)){
			line_number_selectin_cmb.getEditor().setText( "" );
		} else {
			line_number_selectin_cmb.getEditor().setText(editor_text + "0");
		}
	}
	
	public void handleJedan() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "1");
	}
	
	public void handleDva() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "2");
	}
	
	public void handleTri() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "3");
	}
	
	public void handleCetiri() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "4");
	}
	
	public void handlePet() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "5");
	}
	
	public void handleSest() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "6");
	}
	
	public void handleSedam() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "7");
	}
	
	public void handleOsam() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "8");
	}
	
	public void handleDevet() {
		line_number_selectin_cmb.getEditor().setText(line_number_selectin_cmb.getEditor().getText() + "9");
	}
	
	public void handleEnter() {
		
	}
	
	public void handleBackSpace() {
		String editor_text = line_number_selectin_cmb.getEditor().getText();
		if(is_number(editor_text)){
			line_number_selectin_cmb.getEditor().setText( "" );
		} else {
			if(editor_text.length() < 1) {
				return;
			}else {
				String new_text = editor_text.substring(0,editor_text.length() -1);
				line_number_selectin_cmb.getEditor().setText( new_text );
			}
		}
		
		
	}
	

    
    
    private void reset() {
//    	podlinija_cbx.getItems().clear();
//    	smer_cbx.getItems().clear();
//    	reset_combo_box();
    	display_home_screen();
//    	init_set_inivisible();
    }
    
    
    private void init_main_cmb() {
    	

    	
    	ObservableList<LineDataWithNumber> line_items = FXCollections.observableArrayList();
    	line_items.addAll(_line_data.getAllLines());
    	line_number_selectin_cmb.setItems(line_items);
    	
    	//line_number_selectin_cmb.getItems().addAll(_line_data.getAllLines());
    	
        // We need a StringConverter in order to ensure the selected item is displayed properly
        // For this sample, we only want the Person's name to be displayed
    	line_number_selectin_cmb.setConverter(new StringConverter<LineDataWithNumber>() {
            @Override
            public String toString(LineDataWithNumber line) {
            	if(line == null ||  line.get_sub_line() == null) return "";
                return "" + line.get_line_number() + line.get_sub_line();
            }
            
            @Override
            public LineDataWithNumber fromString(String string) {
            	for(LineDataWithNumber current : line_items) {
            		if ( current.equals(string) ) {
            			return current;
            		}
            	}
            	
            	return null;
//            	String[] splt = string.split(":");
//                 return new LineDataWithNumber(Integer.parseInt(splt[0]), splt[1], splt[2], splt[3]);
            }
        });


        // Provide our own CellFactory to control how items are displayed
    	line_number_selectin_cmb.setCellFactory(cell -> new ListCell<LineDataWithNumber>() {
    		
    		//Label prazna_lbl = new Label();
            Label broj_linije_lbl = new Label();
            Label polaziste_lbl = new Label();
            Label odrediste_lbl = new Label();
            


            // Create our layout here to be reused for each ListCell
            GridPane gridPane = new GridPane();

            
            

            // Static block to configure our layout
            {
                // Ensure all our column widths are constant
            	ColumnConstraints co1 = new ColumnConstraints();
//            	co1.setPercentWidth(20);
            	co1.setPrefWidth(100);
            	ColumnConstraints col2 = new ColumnConstraints();
//            	col2.setPercentWidth(80);
            	col2.setPrefWidth(285);
                gridPane.getColumnConstraints().addAll(
                		co1,
                		col2
                );
                
                
                GridPane.setFillWidth(polaziste_lbl, true);
                GridPane.setFillWidth(odrediste_lbl, true);
                
                broj_linije_lbl.setMaxWidth(Double.MAX_VALUE);
                polaziste_lbl.setMaxWidth(Double.MAX_VALUE);
                odrediste_lbl.setMaxWidth(Double.MAX_VALUE);

                broj_linije_lbl.getStyleClass().add("grid_br_linije");
                polaziste_lbl.getStyleClass().add("grid_polaziste");
                odrediste_lbl.getStyleClass().add("grid_odrediste");

                //prazna_lbl.setAlignment(Pos.CENTER_LEFT);
                broj_linije_lbl.setAlignment(Pos.CENTER_LEFT);
                polaziste_lbl.setAlignment(Pos.CENTER_RIGHT);
                odrediste_lbl.setAlignment(Pos.CENTER_RIGHT);
                
                GridPane.setHalignment(polaziste_lbl, HPos.RIGHT);
                GridPane.setHalignment(odrediste_lbl, HPos.RIGHT);
                GridPane.setRowSpan(broj_linije_lbl, 2);
                //GridPane.setHalignment(prazna_lbl, HPos.LEFT);
                //GridPane.setValignment(prazna_lbl, VPos.CENTER);
                GridPane.setHalignment(broj_linije_lbl, HPos.LEFT);
                GridPane.setValignment(broj_linije_lbl, VPos.CENTER);
                
                //gridPane.add(prazna_lbl, 0, 0);
                gridPane.add(broj_linije_lbl, 0, 0,1,2);
                
                gridPane.add(polaziste_lbl, 1, 0);
                gridPane.add(odrediste_lbl, 1, 1);
                


            }

            // We override the updateItem() method in order to provide our own layout for this Cell's graphicProperty
            @Override
            protected void updateItem(LineDataWithNumber line, boolean empty) {
                super.updateItem(line, empty);

                if (!empty && line != null) {

                    // Update our Labels
                	broj_linije_lbl.setText("" + line.get_line_number() + line.get_sub_line());
                	polaziste_lbl.setText(line.get_pocetno_stajaliste());
                	odrediste_lbl.setText(line.get_krajnje_stajaliste());

                    // Set this ListCell's graphicProperty to display our GridPane
                    setGraphic(gridPane);
                } else {
                    // Nothing to display here
                    setGraphic(null);
                }
            }
        });
    	
    	
    	new AutoCompleteBox ( line_number_selectin_cmb );
    	
    	
    }
    
    private void reset_combo_box() {
 
    	line_number_selectin_cmb.getSelectionModel().clearSelection();
    	line_number_selectin_cmb.getEditor().setText("");
    }
   
    

    
//    private void init_set_inivisible() {
////    	podlinija_cbx.setVisible(false);
////    	smer_cbx.setVisible(false);
////    	izaberi_podliniju_lbl.setVisible(false);
////    	izaberi_smer_lbl.setVisible(false);
//    }
    
//    private void initSelectionHandler(ChoiceBox<String> cbx) {
//    	cbx.setOnAction((event) -> {
//    	    boolean selected = cbx.getValue() != null;
//    	    System.out.println("CheckBox Action (selected: " + selected + ")");
//    	    if(selected) {
//    	    	set_podlinija_smer();
//    	    }
//    	});
//    }
    
    private String getSelectedLine() {
    	if(_selected_line == null)return "";
    	return  _selected_line.get_line_number() + _selected_line.get_sub_line() ;
    }
    
    private int getSelectedLineNumber() {
    	if(_selected_line == null) return 1;
    	return  _selected_line.get_line_number();
    }
    
//    private void set_podlinija(int line_number) {
//    	podlinija_cbx.getItems().clear();
//    	//System.out.println("Selektovana linija je " + getSelectedLine());
//    	List<String> podlinija = _line_data.getSublines(line_number);
//    	if((podlinija.size() == 1 && podlinija.get(0).toString().equals("")) || podlinija.size() == 0){
//    		//linija nema podlinije
//    		System.out.println("Linija bez podlinija ");
//    		set_smer();
//    	}else {
//    		podlinija_cbx.getItems().addAll(podlinija);
//
//    		podlinija_cbx.setVisible(true);
//    	}
//
//    	
//    }
    
//    private void set_smer() {
//    	smer_cbx.getItems().clear();
//    	List<String> smer = _line_data.getPocetnoKrajnjeStajaliste(getSelectedLineNumber(), podlinija_cbx.getValue() == null ? "" : podlinija_cbx.getValue());
//    	smer_cbx.getItems().addAll(smer);
//    	smer_cbx.setVisible(true);
//    }
    
    
//    private void setSelectionListeners() {
//
////    	jedinice_cbx.setOnAction((event) -> {
////    	    boolean selected = jedinice_cbx.getValue() != null;
////    	    System.out.println("CheckBox Action (selected: " + selected + ")");
////    	    if(selected) {
////              try {
////              int broj_linije = getSelectedLineNumber();//Integer.parseInt(stotice_cbx.getValue() + desetice_cbx.getValue() + new_val);
////              set_podlinija(broj_linije);
////              }catch(Throwable e) {
////           	   System.out.println("nema veze, reset u pitanju");
////              }
////    	    }
////    	});
//    	
//
//    	
////    	podlinija_cbx.setOnAction((event) -> {
////    	    boolean selected = podlinija_cbx.getValue() != null;
////    	    System.out.println("CheckBox Action (selected: " + selected + ")");
////    	    if(selected) {
////    	    	set_smer();
////    	    }
////    	});
//    }
    
    @Override
    protected byte[]  set_for_dispay(){
    	DisplaySettings disp_sett = new DisplaySettings(Integer.parseInt(getProperties().getProperty("switchg_time","5")));

    	try {
    		byte[] disp_data = DispayUtil.from_cirilic_to_latinic_byte(_current_display);
    		disp_sett.addForDisplay(DisplaySettings.DISPLAY_BACK_KEY, disp_data);
    		disp_sett.addForDisplay(DisplaySettings.DISPLAY_FRONT_KEY, disp_data);
    		String[] parsed = DispayUtil.from_cirilic_to_latinic(_current_display).split(" ");
    		disp_sett.addForDisplay(DisplaySettings.DISPLAY_SIDE_KEY, DispayUtil.from_cirilic_to_latinic_byte(parsed[1]));
    		
    	}catch(Exception e) {
    		System.out.println("Exception when try to prepar data for display, details: " + e.getMessage());
    	}


    	return disp_sett.getForDisplays();
    }
    
    
    
	

}
