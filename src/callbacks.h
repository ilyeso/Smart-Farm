#include <gtk/gtk.h>



void toggled_func(GtkCellRendererToggle *cell_renderer,gchar *paths,gpointer user_data) ;

void
on_authen_clicked                      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonLogin_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeview2_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_buttonRechercheCapteur_clicked      (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonRefresh_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAlerte_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonSupprimerCap_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonModifierCap_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAjoutercap_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonHomeGestCap_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonDeconnexionGcap_clicked       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonGclient_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonGTroup_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonGcap_clicked                  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonGequip_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonGouvr_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_logOutDashboard_clicked             (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAjoutFinalCap_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_modifFinalCap_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAnullerAjout_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_closebutton_AjoutSucc_clicked       (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonValiderSuppCap_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAnnulerSuppCap_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radio_homme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_femme_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_retour_client_individuel_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_ajouter_client_individuel_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_treeview_liste_clients_ind_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_buttonMenu_clicked                  (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAfficherPart_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_supprimer_client_individuel_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modifier_client_particuler_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_ajouter_client_particulier_liste_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_valider_ajout_client_pro_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_button_retour_ajout_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonClientsPart_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonClientsPro_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonOuiAttention_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonNonAttention_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonChercherPro_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_retour_modifier_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_valider_modifier_client_pro_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonChercherInd_clicked           (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_radiobuttonHommeModifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonFemmeModifier_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_button_retour_modifier_client_particulier_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_modifier_client_individuel_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_treeview_liste_clients_pro_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_button_liste_supprimer_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_liste_modifier_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button_liste_ajouter_client_pro_clicked
                                        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAfficherPro_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonOk_clicked                    (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonRetourFail_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAfficher_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonMarquer_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonTauxAbsence_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonTroupChaqType_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_button8_clicked                     (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonValAlarm_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAnneeSeche_clicked            (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonLogOutAdmin_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonDec_GT2_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonMP_GT2_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radiobuttonMale_GT2_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonF_GT2_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonVac_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonMal_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonGes_GT2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonConfirmer_GT2_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAfficher_GT2_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_treeviewGT1_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_buttonMP_GT1_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonDec_GT1_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonMAJ_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAjouter_GT1_clicked           (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonModifier_GT1_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonSupp_GT1_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonDec_AS_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonMP_AS_clicked                 (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonCalculer_clicked              (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonMP_GT3_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonDec_GT3_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_radiobuttonM_GT3_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonF_GT3_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonVac_GT3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonMal_GT3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_checkbuttonGes_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonConfirmer_GT3_clicked         (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonAfficher_GT3_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonSMS_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonRetourCapAdmin_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonLogOutCapAdmin_clicked        (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonOuvrierAnnee_clicked          (GtkWidget       *button,
                                        gpointer         user_data);

void
on_buttonEnvoyerSMS_ADMIN_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonSupprimerInd_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonSupprimerPro_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonRetourSupprimerInd_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonRetourSupprimerPro_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiser_la_page_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonactualiser_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_nbr_de_troupeaux_de_chaque_types_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeviewbestouv_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Afficher_le_nombre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonAFFICHERLOUVDELANNEE_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_dashEmplGclient_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_dashEmplGclientMenu_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_dashEmplGclientPro_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonRech_GT3_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonRech_GT3_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonDec_GTA_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonMP_GTA_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonCalculer_GTA_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonCalculer_AS_clicked           (GtkButton       *button,
                                        gpointer         user_data);
