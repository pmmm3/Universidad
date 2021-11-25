
package GUI;
import civitas.CivitasJuego;
import civitas.Diario;
import civitas.Jugador;
import civitas.OperacionesJuego;
import civitas.SalidasCarcel;
import java.util.ArrayList;

/**
 *
 * @author pc
 */
public class CivitasView extends javax.swing.JFrame {
    CivitasJuego juego;
    JugadorPanel jugadorPanel;
    GestionarDialog gestionarD;
    /**
     * Creates new form CivitasView
     */
    public CivitasView() {
        initComponents();
        jugadorPanel = new JugadorPanel();
        contenedorVistaJugador.add (jugadorPanel);
        gestionarD = new GestionarDialog(this);
        
        repaint();
        revalidate();
    }
    public void setCivitasJuego(CivitasJuego civitas)
    {
        juego = civitas;
        this.actualizarVista();
        setVisible(true);
        
    }
    public void actualizarVista()
    {
        jugadorPanel.setJugador(juego.getJugadorActual());
        txt_casilla.setText(juego.getCasillaActual().toString());
        lb_ranking.setVisible(false);
        txt_ranking.setVisible(false);
        if(juego.finalDelJuego())
        {
            String rank="TOP:\n";
            ArrayList <Jugador> lista =juego.ranking();
            for(Jugador jg : lista)
            {
                rank+="\t"+jg.getNombre()+"\n";
            }
            txt_ranking.setText(rank);
            lb_ranking.setVisible(true);
            txt_ranking.setVisible(true);
            
        }
        pack();
        repaint();
        revalidate();
    }
    void mostrarSiguienteOperacion(OperacionesJuego next_ope)
    {
        txt_next_operacion.setText(next_ope.toString());
        actualizarVista();
    }
    void mostrarEventos() {
        if(Diario.getInstance().eventosPendientes()) {
            DiarioDialog diarioD= new DiarioDialog(this); //crea la ventana del diario
        }
        

    }
    Respuestas comprar()
    {
        
        int opcion= pregunta.showConfirmDialog(null, "¿Quieres comprar la calle actual?","Compra", pregunta.YES_NO_OPTION);
        
        if(opcion==0)
        {
            return Respuestas.SI;
        }
        else
        {
            return Respuestas.NO;
        }
    }
    void gestionar()
    {
        gestionarD.gestionar(juego.getJugadorActual());
        gestionarD.pack();
        gestionarD.repaint();
        gestionarD.revalidate();
        gestionarD.setVisible(true);
    }
    int getGestion()
    {
        return gestionarD.getGestion();
    }
    
    int getPropiedad()
    {
        return gestionarD.getPropiedad();
    }
    SalidasCarcel salirCarcel()
    {
        String[] opciones= {"SALIR PAGANDO", "SALIR TIRANDO"};
        int respuesta= c_salirCarcel.showOptionDialog(null, "¿Cómo quieres salir de la cárcel?","Salir de la cárcel", c_salirCarcel.DEFAULT_OPTION,c_salirCarcel.QUESTION_MESSAGE,null, opciones, opciones[0] );
        
        if(respuesta==0)
        {
            return SalidasCarcel.PAGANDO;
        }
        else
            return SalidasCarcel.TIRANDO;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        pregunta = new javax.swing.JOptionPane();
        c_salirCarcel = new javax.swing.JOptionPane();
        Titulo = new javax.swing.JLabel();
        contenedorVistaJugador = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        txt_next_operacion = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        txt_casilla = new javax.swing.JTextArea();
        lb_ranking = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        txt_ranking = new javax.swing.JTextArea();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addContainerListener(new java.awt.event.ContainerAdapter() {
            public void componentAdded(java.awt.event.ContainerEvent evt) {
                formComponentAdded(evt);
            }
        });

        Titulo.setFont(new java.awt.Font("Ubuntu", 1, 15)); // NOI18N
        Titulo.setText("CivitasViuw");
        Titulo.setVerticalAlignment(javax.swing.SwingConstants.TOP);
        Titulo.setEnabled(false);

        contenedorVistaJugador.setPreferredSize(new java.awt.Dimension(220, 278));

        jLabel1.setFont(new java.awt.Font("Waree", 0, 14)); // NOI18N
        jLabel1.setText("Siguiente Operación: ");
        jLabel1.setEnabled(false);

        txt_next_operacion.setFont(new java.awt.Font("Waree", 0, 12)); // NOI18N
        txt_next_operacion.setEnabled(false);
        txt_next_operacion.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                txt_next_operacionActionPerformed(evt);
            }
        });

        txt_casilla.setColumns(20);
        txt_casilla.setFont(new java.awt.Font("Waree", 0, 14)); // NOI18N
        txt_casilla.setRows(5);
        txt_casilla.setDisabledTextColor(java.awt.Color.black);
        txt_casilla.setEnabled(false);
        jScrollPane1.setViewportView(txt_casilla);

        lb_ranking.setFont(new java.awt.Font("Waree", 0, 14)); // NOI18N
        lb_ranking.setText("Ranking:");
        lb_ranking.setEnabled(false);

        txt_ranking.setEditable(false);
        txt_ranking.setColumns(20);
        txt_ranking.setFont(new java.awt.Font("Waree", 1, 10)); // NOI18N
        txt_ranking.setRows(5);
        txt_ranking.setDisabledTextColor(java.awt.Color.black);
        txt_ranking.setEnabled(false);
        txt_ranking.setOpaque(false);
        jScrollPane2.setViewportView(txt_ranking);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addGap(18, 18, 18)
                        .addComponent(txt_next_operacion)
                        .addGap(20, 20, 20))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(Titulo)
                        .addGap(258, 258, 258))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(jScrollPane2, javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(lb_ranking, javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 319, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(contenedorVistaJugador, javax.swing.GroupLayout.DEFAULT_SIZE, 266, Short.MAX_VALUE)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(Titulo)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 249, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(lb_ranking)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 139, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(contenedorVistaJugador, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGap(18, 18, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(txt_next_operacion, javax.swing.GroupLayout.PREFERRED_SIZE, 24, Short.MAX_VALUE)))
        );

        Titulo.getAccessibleContext().setAccessibleName("Titulo");
        Titulo.getAccessibleContext().setAccessibleDescription("label de titulo");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void formComponentAdded(java.awt.event.ContainerEvent evt) {//GEN-FIRST:event_formComponentAdded
        // TODO add your handling code here:
    }//GEN-LAST:event_formComponentAdded

    private void txt_next_operacionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_txt_next_operacionActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_txt_next_operacionActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(CivitasView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(CivitasView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(CivitasView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(CivitasView.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new CivitasView().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel Titulo;
    private javax.swing.JOptionPane c_salirCarcel;
    private javax.swing.JPanel contenedorVistaJugador;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JLabel lb_ranking;
    private javax.swing.JOptionPane pregunta;
    private javax.swing.JTextArea txt_casilla;
    private javax.swing.JTextField txt_next_operacion;
    private javax.swing.JTextArea txt_ranking;
    // End of variables declaration//GEN-END:variables
}