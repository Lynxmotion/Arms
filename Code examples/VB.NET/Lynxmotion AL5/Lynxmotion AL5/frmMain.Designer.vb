<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmMain
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.hsbBase = New System.Windows.Forms.HScrollBar()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.lblWristRotate = New System.Windows.Forms.Label()
        Me.hsbWristRotate = New System.Windows.Forms.HScrollBar()
        Me.nudWristRotate = New System.Windows.Forms.NumericUpDown()
        Me.lblGripper = New System.Windows.Forms.Label()
        Me.hsbGripper = New System.Windows.Forms.HScrollBar()
        Me.nudGripper = New System.Windows.Forms.NumericUpDown()
        Me.lblWrist = New System.Windows.Forms.Label()
        Me.hsbWrist = New System.Windows.Forms.HScrollBar()
        Me.nudWrist = New System.Windows.Forms.NumericUpDown()
        Me.lblElbow = New System.Windows.Forms.Label()
        Me.hsbElbow = New System.Windows.Forms.HScrollBar()
        Me.nudElbow = New System.Windows.Forms.NumericUpDown()
        Me.lblSoulder = New System.Windows.Forms.Label()
        Me.hsbShoulder = New System.Windows.Forms.HScrollBar()
        Me.nudShoulder = New System.Windows.Forms.NumericUpDown()
        Me.lblBase = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.nudBase = New System.Windows.Forms.NumericUpDown()
        Me.Panel1.SuspendLayout()
        CType(Me.nudWristRotate, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudGripper, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudWrist, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudElbow, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudShoulder, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.nudBase, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'hsbBase
        '
        Me.hsbBase.Location = New System.Drawing.Point(115, 20)
        Me.hsbBase.Maximum = 2500
        Me.hsbBase.Minimum = 500
        Me.hsbBase.Name = "hsbBase"
        Me.hsbBase.Size = New System.Drawing.Size(254, 20)
        Me.hsbBase.TabIndex = 0
        Me.hsbBase.Tag = "0"
        Me.hsbBase.Value = 1500
        '
        'Panel1
        '
        Me.Panel1.BackColor = System.Drawing.Color.Maroon
        Me.Panel1.Controls.Add(Me.Label13)
        Me.Panel1.Controls.Add(Me.Label12)
        Me.Panel1.Controls.Add(Me.Label11)
        Me.Panel1.Controls.Add(Me.Label10)
        Me.Panel1.Controls.Add(Me.Label9)
        Me.Panel1.Controls.Add(Me.Label8)
        Me.Panel1.Controls.Add(Me.lblWristRotate)
        Me.Panel1.Controls.Add(Me.hsbWristRotate)
        Me.Panel1.Controls.Add(Me.nudWristRotate)
        Me.Panel1.Controls.Add(Me.lblGripper)
        Me.Panel1.Controls.Add(Me.hsbGripper)
        Me.Panel1.Controls.Add(Me.nudGripper)
        Me.Panel1.Controls.Add(Me.lblWrist)
        Me.Panel1.Controls.Add(Me.hsbWrist)
        Me.Panel1.Controls.Add(Me.nudWrist)
        Me.Panel1.Controls.Add(Me.lblElbow)
        Me.Panel1.Controls.Add(Me.hsbElbow)
        Me.Panel1.Controls.Add(Me.nudElbow)
        Me.Panel1.Controls.Add(Me.lblSoulder)
        Me.Panel1.Controls.Add(Me.hsbShoulder)
        Me.Panel1.Controls.Add(Me.nudShoulder)
        Me.Panel1.Controls.Add(Me.lblBase)
        Me.Panel1.Controls.Add(Me.hsbBase)
        Me.Panel1.Controls.Add(Me.Label2)
        Me.Panel1.Controls.Add(Me.Label1)
        Me.Panel1.Controls.Add(Me.nudBase)
        Me.Panel1.Location = New System.Drawing.Point(12, 12)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(422, 164)
        Me.Panel1.TabIndex = 1
        '
        'Label13
        '
        Me.Label13.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label13.Location = New System.Drawing.Point(3, 140)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(61, 20)
        Me.Label13.TabIndex = 24
        Me.Label13.Text = "Wrist rotate"
        Me.Label13.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label12
        '
        Me.Label12.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label12.Location = New System.Drawing.Point(3, 116)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(61, 20)
        Me.Label12.TabIndex = 23
        Me.Label12.Text = "Gripper"
        Me.Label12.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label11
        '
        Me.Label11.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label11.Location = New System.Drawing.Point(3, 92)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(61, 20)
        Me.Label11.TabIndex = 22
        Me.Label11.Text = "Wrist"
        Me.Label11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label10
        '
        Me.Label10.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label10.Location = New System.Drawing.Point(3, 68)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(61, 20)
        Me.Label10.TabIndex = 21
        Me.Label10.Text = "Elbow"
        Me.Label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label9
        '
        Me.Label9.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label9.Location = New System.Drawing.Point(3, 44)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(61, 20)
        Me.Label9.TabIndex = 20
        Me.Label9.Text = "Shoulder"
        Me.Label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label8
        '
        Me.Label8.BackColor = System.Drawing.SystemColors.ControlDark
        Me.Label8.Location = New System.Drawing.Point(3, 20)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(61, 20)
        Me.Label8.TabIndex = 19
        Me.Label8.Text = "Base"
        Me.Label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'lblWristRotate
        '
        Me.lblWristRotate.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblWristRotate.Location = New System.Drawing.Point(372, 140)
        Me.lblWristRotate.Name = "lblWristRotate"
        Me.lblWristRotate.Size = New System.Drawing.Size(46, 20)
        Me.lblWristRotate.TabIndex = 18
        Me.lblWristRotate.Tag = "5"
        Me.lblWristRotate.Text = "1500"
        Me.lblWristRotate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'hsbWristRotate
        '
        Me.hsbWristRotate.Location = New System.Drawing.Point(115, 140)
        Me.hsbWristRotate.Maximum = 2500
        Me.hsbWristRotate.Minimum = 500
        Me.hsbWristRotate.Name = "hsbWristRotate"
        Me.hsbWristRotate.Size = New System.Drawing.Size(254, 20)
        Me.hsbWristRotate.TabIndex = 5
        Me.hsbWristRotate.Tag = "5"
        Me.hsbWristRotate.Value = 1500
        '
        'nudWristRotate
        '
        Me.nudWristRotate.Location = New System.Drawing.Point(66, 140)
        Me.nudWristRotate.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudWristRotate.Name = "nudWristRotate"
        Me.nudWristRotate.Size = New System.Drawing.Size(46, 20)
        Me.nudWristRotate.TabIndex = 15
        Me.nudWristRotate.Tag = "5"
        Me.nudWristRotate.Value = New Decimal(New Integer() {5, 0, 0, 0})
        '
        'lblGripper
        '
        Me.lblGripper.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblGripper.Location = New System.Drawing.Point(372, 116)
        Me.lblGripper.Name = "lblGripper"
        Me.lblGripper.Size = New System.Drawing.Size(46, 20)
        Me.lblGripper.TabIndex = 15
        Me.lblGripper.Tag = "4"
        Me.lblGripper.Text = "1500"
        Me.lblGripper.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'hsbGripper
        '
        Me.hsbGripper.Location = New System.Drawing.Point(115, 116)
        Me.hsbGripper.Maximum = 2500
        Me.hsbGripper.Minimum = 500
        Me.hsbGripper.Name = "hsbGripper"
        Me.hsbGripper.Size = New System.Drawing.Size(254, 20)
        Me.hsbGripper.TabIndex = 4
        Me.hsbGripper.Tag = "4"
        Me.hsbGripper.Value = 1500
        '
        'nudGripper
        '
        Me.nudGripper.Location = New System.Drawing.Point(66, 116)
        Me.nudGripper.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudGripper.Name = "nudGripper"
        Me.nudGripper.Size = New System.Drawing.Size(46, 20)
        Me.nudGripper.TabIndex = 14
        Me.nudGripper.Tag = "4"
        Me.nudGripper.Value = New Decimal(New Integer() {4, 0, 0, 0})
        '
        'lblWrist
        '
        Me.lblWrist.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblWrist.Location = New System.Drawing.Point(372, 92)
        Me.lblWrist.Name = "lblWrist"
        Me.lblWrist.Size = New System.Drawing.Size(46, 20)
        Me.lblWrist.TabIndex = 12
        Me.lblWrist.Tag = "3"
        Me.lblWrist.Text = "1500"
        Me.lblWrist.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'hsbWrist
        '
        Me.hsbWrist.Location = New System.Drawing.Point(115, 92)
        Me.hsbWrist.Maximum = 2500
        Me.hsbWrist.Minimum = 500
        Me.hsbWrist.Name = "hsbWrist"
        Me.hsbWrist.Size = New System.Drawing.Size(254, 20)
        Me.hsbWrist.TabIndex = 3
        Me.hsbWrist.Tag = "3"
        Me.hsbWrist.Value = 1500
        '
        'nudWrist
        '
        Me.nudWrist.Location = New System.Drawing.Point(66, 92)
        Me.nudWrist.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudWrist.Name = "nudWrist"
        Me.nudWrist.Size = New System.Drawing.Size(46, 20)
        Me.nudWrist.TabIndex = 13
        Me.nudWrist.Tag = "3"
        Me.nudWrist.Value = New Decimal(New Integer() {3, 0, 0, 0})
        '
        'lblElbow
        '
        Me.lblElbow.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblElbow.Location = New System.Drawing.Point(372, 68)
        Me.lblElbow.Name = "lblElbow"
        Me.lblElbow.Size = New System.Drawing.Size(46, 20)
        Me.lblElbow.TabIndex = 9
        Me.lblElbow.Tag = "2"
        Me.lblElbow.Text = "1500"
        Me.lblElbow.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'hsbElbow
        '
        Me.hsbElbow.Location = New System.Drawing.Point(115, 68)
        Me.hsbElbow.Maximum = 2500
        Me.hsbElbow.Minimum = 500
        Me.hsbElbow.Name = "hsbElbow"
        Me.hsbElbow.Size = New System.Drawing.Size(254, 20)
        Me.hsbElbow.TabIndex = 2
        Me.hsbElbow.Tag = "2"
        Me.hsbElbow.Value = 1500
        '
        'nudElbow
        '
        Me.nudElbow.Location = New System.Drawing.Point(66, 68)
        Me.nudElbow.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudElbow.Name = "nudElbow"
        Me.nudElbow.Size = New System.Drawing.Size(46, 20)
        Me.nudElbow.TabIndex = 12
        Me.nudElbow.Tag = "2"
        Me.nudElbow.Value = New Decimal(New Integer() {2, 0, 0, 0})
        '
        'lblSoulder
        '
        Me.lblSoulder.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblSoulder.Location = New System.Drawing.Point(372, 44)
        Me.lblSoulder.Name = "lblSoulder"
        Me.lblSoulder.Size = New System.Drawing.Size(46, 20)
        Me.lblSoulder.TabIndex = 6
        Me.lblSoulder.Tag = "1"
        Me.lblSoulder.Text = "1500"
        Me.lblSoulder.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'hsbShoulder
        '
        Me.hsbShoulder.Location = New System.Drawing.Point(115, 44)
        Me.hsbShoulder.Maximum = 2500
        Me.hsbShoulder.Minimum = 500
        Me.hsbShoulder.Name = "hsbShoulder"
        Me.hsbShoulder.Size = New System.Drawing.Size(254, 20)
        Me.hsbShoulder.TabIndex = 1
        Me.hsbShoulder.Tag = "1"
        Me.hsbShoulder.Value = 1500
        '
        'nudShoulder
        '
        Me.nudShoulder.Location = New System.Drawing.Point(66, 44)
        Me.nudShoulder.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudShoulder.Name = "nudShoulder"
        Me.nudShoulder.Size = New System.Drawing.Size(46, 20)
        Me.nudShoulder.TabIndex = 11
        Me.nudShoulder.Tag = "1"
        Me.nudShoulder.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'lblBase
        '
        Me.lblBase.BackColor = System.Drawing.SystemColors.ControlDark
        Me.lblBase.Location = New System.Drawing.Point(372, 20)
        Me.lblBase.Name = "lblBase"
        Me.lblBase.Size = New System.Drawing.Size(46, 20)
        Me.lblBase.TabIndex = 3
        Me.lblBase.Tag = "0"
        Me.lblBase.Text = "1500"
        Me.lblBase.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.Color.DarkGray
        Me.Label2.Location = New System.Drawing.Point(115, 4)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(303, 13)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Signal value"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.Color.DarkGray
        Me.Label1.Location = New System.Drawing.Point(3, 4)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(110, 13)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Channel"
        '
        'nudBase
        '
        Me.nudBase.Location = New System.Drawing.Point(66, 20)
        Me.nudBase.Maximum = New Decimal(New Integer() {31, 0, 0, 0})
        Me.nudBase.Name = "nudBase"
        Me.nudBase.Size = New System.Drawing.Size(46, 20)
        Me.nudBase.TabIndex = 10
        Me.nudBase.Tag = "0"
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(446, 188)
        Me.Controls.Add(Me.Panel1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D
        Me.Name = "frmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Lynxmotion AL5 (VB.NET example)"
        Me.Panel1.ResumeLayout(False)
        CType(Me.nudWristRotate, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudGripper, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudWrist, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudElbow, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudShoulder, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.nudBase, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents hsbBase As System.Windows.Forms.HScrollBar
    Friend WithEvents Panel1 As System.Windows.Forms.Panel
    Friend WithEvents Label13 As System.Windows.Forms.Label
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents lblWristRotate As System.Windows.Forms.Label
    Friend WithEvents hsbWristRotate As System.Windows.Forms.HScrollBar
    Friend WithEvents nudWristRotate As System.Windows.Forms.NumericUpDown
    Friend WithEvents lblGripper As System.Windows.Forms.Label
    Friend WithEvents hsbGripper As System.Windows.Forms.HScrollBar
    Friend WithEvents nudGripper As System.Windows.Forms.NumericUpDown
    Friend WithEvents lblWrist As System.Windows.Forms.Label
    Friend WithEvents hsbWrist As System.Windows.Forms.HScrollBar
    Friend WithEvents nudWrist As System.Windows.Forms.NumericUpDown
    Friend WithEvents lblElbow As System.Windows.Forms.Label
    Friend WithEvents hsbElbow As System.Windows.Forms.HScrollBar
    Friend WithEvents nudElbow As System.Windows.Forms.NumericUpDown
    Friend WithEvents lblSoulder As System.Windows.Forms.Label
    Friend WithEvents hsbShoulder As System.Windows.Forms.HScrollBar
    Friend WithEvents nudShoulder As System.Windows.Forms.NumericUpDown
    Friend WithEvents lblBase As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents nudBase As System.Windows.Forms.NumericUpDown

End Class
