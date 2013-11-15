/********************************/
/*								              */
/* DECLARACION DE LAS FUNCIONES */
/*								              */
/********************************/

//Inicializa la ventana principal
void initialize_window(GtkWidget *window, int x, int y);
//Cierra la ventana principal, y con esta las que esten abiertas
static void destroy(GtkWidget *widget,gpointer data);
//Cuando el checkbox de 1 ejemplo es seleccionado
static void checkMax_selected(GtkWidget *widget, GtkWidget *checkbox);
//Cuando el checkbox de 1000 ejemplos es seleccionado
static void checkMin_selected(GtkWidget *widget, GtkWidget *checkbox);
//
static void pasar_variables(GtkWidget *widget, GtkWidget *entry);
//
static void pasar_restricciones(GtkWidget *widget, GtkWidget *entry);
//
static void iniciar_nueva_ventana();
//inserta los labels y entries para la funcion objetivo
void insertar_funcion_objetivo(GtkWidget *table);
//inserta los labels, entries y combos para las restricciones
void insertar_restricciones(GtkWidget *table);
//
static void imprimir_campos();
//guarda en un arreglo las variables que el usuario escribio en la funcion objetivo
static void guardar_funcion_objetivo();
//guarda en una matriz las variables q el usuario uso en las restricciones
static void guardar_restricciones();



/*************************************/
/*								     */
/* DECLARACION DE VARIABLES GLOBALES */
/*							         */
/*************************************/

GtkWidget *window;

// 1 maximizar / 0 minimizar
int objetivo = 1;
int cantidadVariables = 0;
int cantidadRestricciones = 0;
GtkWidget **funcionObjetivo;
float *funcionObjetivoVariables;
GtkWidget **restricciones;
float *restriccionesVariables;



/***********************************/
/*								                 */
/* IMPLEMENTACION DE LAS FUNCIONES */
/*								                 */
/***********************************/

void initialize_window(GtkWidget *window, int x, int y)
{
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"Árboles Binarios");
    gtk_window_set_default_size (GTK_WINDOW (window), x*80, y*80);
    g_signal_connect (window, "destroy",G_CALLBACK (destroy), NULL);
    gtk_widget_show_all(window);
}

static void destroy(GtkWidget *widget,gpointer data)
{
    gtk_main_quit ();
}

static void checkMax_selected(GtkWidget *widget, GtkWidget *checkbox)
{
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), FALSE);
      objetivo = 1;
  }
  else
  {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), TRUE);
      objetivo = 0;
  }
}

static void checkMin_selected(GtkWidget *widget, GtkWidget *checkbox)
{
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), FALSE);
      objetivo = 0;
  }
  else
  {
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), TRUE);
      objetivo = 1;
  }
}

static void pasar_variables(GtkWidget *widget, GtkWidget *entry)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    cantidadVariables = atoi(entry_text);  
    if (cantidadVariables < 2)
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                  GTK_DIALOG_DESTROY_WITH_PARENT,
                  GTK_MESSAGE_INFO,
                  GTK_BUTTONS_OK,
                  "El número de restricciones es un valor\n\nnumerico y mayor a 1.");
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else
    {
        //cantidadVariables = 0;
    }
}

static void pasar_restricciones(GtkWidget *widget, GtkWidget *entry)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
    cantidadRestricciones = atoi(entry_text);  
    if (cantidadRestricciones < 2)
    {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                  GTK_DIALOG_DESTROY_WITH_PARENT,
                  GTK_MESSAGE_INFO,
                  GTK_BUTTONS_OK,
                  "El número de restricciones es un valor\n\nnumerico y mayor a 1.");
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else
    {
        if(cantidadVariables > 1)
        {
            iniciar_nueva_ventana();
        }
    }
}

static void iniciar_nueva_ventana()
{
    GtkWidget *dialog, *content_area, *scrolled_window, *viewport, *darea, *table, *button_aceptar;


    dialog = gtk_dialog_new_with_buttons ("Comparaciones", GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, 
                                            GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);
    g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

    //table = gtk_table_new(5, 6, TRUE);
    table = gtk_grid_new ();
    //gtk_grid_set_column_homogeneous(GTK_GRID (table), TRUE);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    gtk_box_pack_start (GTK_BOX (content_area), scrolled_window, TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);
    
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), table);

    gtk_widget_set_size_request(dialog, 200, 300);

    
    insertar_funcion_objetivo(table);
    insertar_restricciones(table);

    button_aceptar = gtk_button_new_with_label ("Aceptar");
    gtk_grid_attach (GTK_GRID (table),button_aceptar,0, 4, 1, 1);
    //Cuando el boton_aceptar es precionado
    g_signal_connect(button_aceptar, "clicked", 
        G_CALLBACK(guardar_restricciones), NULL);
  

    gtk_widget_show_all(dialog);
}

void insertar_funcion_objetivo(GtkWidget *table)
{
    funcionObjetivo = realloc(funcionObjetivo, cantidadVariables * sizeof(GtkWidget));    
    GtkWidget *label, *entrada;
    //Funcion Objetivo
    if (objetivo)
    {
        label = gtk_label_new ("Maximizar");
    }
    else
    {
        label = gtk_label_new ("Minimizar");
    }    
    gtk_grid_attach (GTK_GRID (table),label, 0, 0, 1, 1);
    label = gtk_label_new (" Z = ");
    gtk_grid_attach (GTK_GRID (table),label, 0, 1, 1, 1);
    int i;
    int j = 0;
    for (i = 0; i < cantidadVariables; i++)
    {
        char var[3];
        sprintf(var, "X%d", i+1);
        label = gtk_label_new(var);

        entrada = gtk_entry_new ();
        gtk_entry_set_max_length (GTK_ENTRY (entrada),5);
        gtk_widget_set_size_request(entrada, 100, 5);

        funcionObjetivo[i] = entrada;
        
        if(i == 0)
        {
            gtk_grid_attach (GTK_GRID (table),label, i+1, 0, 1, 1);            
            gtk_grid_attach (GTK_GRID (table),entrada, i+1, 1, 1, 1);
        }
        else
        {            
            gtk_grid_attach (GTK_GRID (table),label, i+2+j, 0, 1, 1);

            label = gtk_label_new("+");
            gtk_grid_attach (GTK_GRID (table),label, i+1+j, 1, 1, 1);

            gtk_grid_attach (GTK_GRID (table),entrada, i+2+j, 1, 1, 1); 
            j++;
        }        
    }
}

void insertar_restricciones(GtkWidget *table)
{
    restricciones = realloc(restricciones,  (cantidadVariables + 2) * 
                                            cantidadRestricciones * 
                                            sizeof(GtkWidget));

    GtkWidget *label, *entrada, *combo;

    label = gtk_label_new ("Sujeto a: "); 
    gtk_grid_attach (GTK_GRID (table),label, 0, 2, 1, 1);

    int i;
    int k;
   
    for (k = 0; k < cantidadRestricciones; k++)
    {
        //printf("Pase %d\n", cantidadRestricciones);
        int j = 0;
        for (i = 0; i < cantidadVariables; i++)
        {
            entrada = gtk_entry_new ();
            gtk_entry_set_max_length (GTK_ENTRY (entrada),5);
            gtk_widget_set_size_request(entrada, 5, 5);

            restricciones[k + i * cantidadVariables] = entrada;
            
            if(i == 0)
            {            
                gtk_grid_attach (GTK_GRID (table),entrada, i+1, k+3, 1, 1);
            }
            else if(i == (cantidadVariables - 1))
            {
                label = gtk_label_new("+");
                gtk_grid_attach (GTK_GRID (table),label, i+1+j, k+3, 1, 1);

                gtk_grid_attach (GTK_GRID (table),entrada, i+2+j, k+3, 1, 1); 
                j++;

                combo =  gtk_combo_box_text_new();
                gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "<=");
                gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, ">=");
                gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combo), NULL, "=");
                gtk_grid_attach (GTK_GRID (table),combo, i+2+j, k+3, 1, 1);
                j++;

                restricciones[k + (i+1) * cantidadVariables] = combo;

                entrada = gtk_entry_new ();
                gtk_entry_set_max_length (GTK_ENTRY (entrada),5);
                gtk_widget_set_size_request(entrada, 5, 5);
                gtk_grid_attach (GTK_GRID (table),entrada, i+2+j, k+3, 1, 1);

                //restricciones[(k+1) + i * cantidadVariables] = entrada;
                restricciones[k + (i+2) * cantidadVariables] = entrada;
            }
            else
            {            
                label = gtk_label_new("+");
                gtk_grid_attach (GTK_GRID (table),label, i+1+j, k+3, 1, 1);

                gtk_grid_attach (GTK_GRID (table),entrada, i+2+j, k+3, 1, 1); 
                j++;
            }        
        }
    }
}

static void guardar_variables_objetivo()
{
    int i;
    funcionObjetivoVariables =  realloc(funcionObjetivoVariables, cantidadVariables* sizeof(float));
    for (i = 0; i < cantidadVariables; i++)
    {
        GtkWidget *temp = funcionObjetivo[i];
        const gchar *entry_text;
        entry_text = gtk_entry_get_text (GTK_ENTRY (temp));
        float var = (float) atof(entry_text); 
        funcionObjetivoVariables[i] = var;
    }
}

static void guardar_restricciones()
{
    int i;
    int j;
    restriccionesVariables =  realloc(restriccionesVariables, (cantidadVariables + 2) * 
                                                              cantidadRestricciones * 
                                                              sizeof(float));
    for (i = 0; i < cantidadRestricciones; i++)
    {
        for (j = 0; j < cantidadVariables + 2; j++)
        {
            if (j == cantidadVariables)
            {
                GtkWidget *temp = restricciones[i + j * cantidadVariables];
                const gchar *entry_text;
                entry_text =  gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(temp));
                printf("%s\t", entry_text);
            }
            else
            {
                GtkWidget *temp = restricciones[i + j * cantidadVariables];
                const gchar *entry_text;
                entry_text = gtk_entry_get_text (GTK_ENTRY (temp));
                float var = (float) atof(entry_text);
                printf("%f\t", var);
            }
            //float var = 0.0;
            //funcionObjetivoVariables[i] = var;
            
        }        
        printf("\n");
    }
}