Public Class frmMain

    'Constants
    Public Const CST_CHANNEL_ALL As Integer = -1
    Public Const CST_CHANNEL_MINIMUM As Integer = 0
    Public Const CST_CHANNEL_MAXIMUM As Integer = 31
    Public Const CST_SIGNAL_MINIMUM_us As Integer = 500
    Public Const CST_SIGNAL_MAXIMUM_us As Integer = 2500
    Public Const CST_SIGNAL_CENTER_us As Integer = 1500

    Public Const CST_DEFUALT_BAUD_RATE As Integer = 9600

    Public Channels(5) As sInterfaceChannel
    Public SerialPortName As String = ""
    Public SerialPort As IO.Ports.SerialPort
    Public BaudRate As Integer = CST_DEFUALT_BAUD_RATE

    Private Sub frmMain_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        'Obtain baud rate
        Me.BaudRate = Me.GetBaudRate()

        'Obtain port name
        Me.SerialPortName = Me.GetPortName()
        If (String.IsNullOrWhiteSpace(Me.SerialPortName)) Then

            'No port select, close application
            Me.Close()
            End

        End If

        'Open the port
        Try

            Me.SerialPort = My.Computer.Ports.OpenSerialPort(Me.SerialPortName, Me.BaudRate, IO.Ports.Parity.None, 8, IO.Ports.StopBits.One)

        Catch ex As Exception

            MessageBox.Show(ex.Message, "Lynxmotion AL5 Configuration", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Me.Close()
            End

        End Try

        'Check if the port was opened
        If (Not Me.SerialPort.IsOpen) Then

            MessageBox.Show("Unable to open port. Unkown error.", "Lynxmotion AL5 Configuration", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Me.Close()
            End

        End If

        'Create list of componennts
        Channels(0) = New sInterfaceChannel(Me.nudBase, Me.hsbBase, Me.lblBase)
        Channels(1) = New sInterfaceChannel(Me.nudShoulder, Me.hsbShoulder, Me.lblSoulder)
        Channels(2) = New sInterfaceChannel(Me.nudElbow, Me.hsbElbow, Me.lblElbow)
        Channels(3) = New sInterfaceChannel(Me.nudWrist, Me.hsbWrist, Me.lblWrist)
        Channels(4) = New sInterfaceChannel(Me.nudGripper, Me.hsbGripper, Me.lblGripper)
        Channels(5) = New sInterfaceChannel(Me.nudWristRotate, Me.hsbWristRotate, Me.lblWristRotate)

        For I As Integer = 0 To 5

            'Set parameters
            With Channels(I).Number

                .Minimum = CST_CHANNEL_MINIMUM
                .Maximum = CST_CHANNEL_MAXIMUM
                .Value = I

            End With

            With Channels(I).Scroll

                .Minimum = CST_SIGNAL_MINIMUM_us
                .Maximum = (CST_SIGNAL_MAXIMUM_us + (.LargeChange - 1))     ' Need to add (LargeChange - 1) to obtain full range
                .Value = CST_SIGNAL_CENTER_us

            End With

            With Channels(I).Label

                .TextAlign = ContentAlignment.MiddleCenter
                .Text = Channels(I).Scroll.Value.ToString

            End With

            'Set handlers for interface events
            AddHandler Channels(I).Scroll.Scroll, AddressOf Me.hsbSignal_Scroll

        Next

        'Update all channels
        Me.UpdateController()

    End Sub

    Private Sub UpdateController(Optional ByVal Index As Integer = CST_CHANNEL_ALL)

        Dim Message As String = ""

        If (Index = CST_CHANNEL_ALL) Then

            'Create a message to update all positions
            For I As Integer = Me.Channels.GetLowerBound(0) To Me.Channels.GetUpperBound(0)

                Message &= "#" & Me.Channels(I).GetChannelValue & " P" & Me.Channels(I).GetSignalValue & " "

            Next

        Else

            If (Index < Me.Channels.GetLowerBound(0)) Then Index = Me.Channels.GetLowerBound(0)
            If (Index > Me.Channels.GetUpperBound(0)) Then Index = Me.Channels.GetUpperBound(0)
            Message &= "#" & Me.Channels(Index).GetChannelValue & " P" & Me.Channels(Index).GetSignalValue & " "

        End If

        'Termination required by the protocol
        Message &= vbCrLf

        'Send the message
        Try

            Me.SerialPort.Write(Message)

        Catch ex As Exception

            MessageBox.Show(ex.Message, "Lynxmotion AL5 Configuration", MessageBoxButtons.OK, MessageBoxIcon.Error)

        End Try

    End Sub

#Region " Support functions "

    Public Function GetBaudRate() As Integer

        Dim Text As String
        Dim Value As Integer = CST_DEFUALT_BAUD_RATE

        Text = InputBox("Enter baud rate", "Lynxmotion AL5 Configuration", CST_DEFUALT_BAUD_RATE.ToString)
        If (String.IsNullOrWhiteSpace(Text)) Then

            'No value entered, use default baud rate

        Else

            Try

                'Value was entered, try to convert
                Value = CInt(Val(Text))

            Catch ex As Exception

                'Conversion failed, use default baud rate

            End Try

        End If

        Return (Value)

    End Function

    Public Function GetPortName() As String

        Dim Value As String = ""

        Dim NumPorts As Integer = (My.Computer.Ports.SerialPortNames.Count - 1)
        Dim ListPorts(NumPorts) As String
        My.Computer.Ports.SerialPortNames.CopyTo(ListPorts, 0)

        For Each Port As String In ListPorts

            'Ask user for using this port
            If (MessageBox.Show("Use port [" & Port & "]?", "Lynxmotion AL5 Configuration", MessageBoxButtons.YesNo, MessageBoxIcon.Question) = Windows.Forms.DialogResult.Yes) Then

                Value = Port
                Exit For

            End If

        Next

        Return (Value)

    End Function

#End Region

#Region " Interface events "

    Private Sub hsbSignal_Scroll(sender As Object, e As ScrollEventArgs)

        Dim I As Integer = CInt(CType(sender, HScrollBar).Tag)

        'Update proper channel
        Channels(I).Label.Text = Channels(I).Scroll.Value.ToString
        UpdateController(I)

    End Sub

    Private Sub frmMain_FormClosed(sender As Object, e As FormClosedEventArgs) Handles Me.FormClosed

        Try

            'If port exists and is open, close it
            If ((Me.SerialPort IsNot Nothing) AndAlso (Me.SerialPort.IsOpen)) Then

                Me.SerialPort.Close()

            End If

        Catch ex As Exception

            MessageBox.Show("Error while closing port [" & Me.SerialPortName & "]", "Lynxmotion AL5 Configuration", MessageBoxButtons.OK, MessageBoxIcon.Error)

        End Try

    End Sub

#End Region

End Class

Public Structure sInterfaceChannel

    Public Number As NumericUpDown
    Public Scroll As HScrollBar
    Public Label As Label

    Public Sub New(ByRef mNumber As NumericUpDown, ByRef mScroll As HScrollBar, ByRef mLabel As Label)

        With Me

            .Number = mNumber
            .Scroll = mScroll
            .Label = mLabel

        End With

    End Sub

    Public ReadOnly Property GetChannelValue As String

        Get

            Return (Me.Number.Value.ToString)

        End Get

    End Property

    Public ReadOnly Property GetSignalValue As String

        Get

            Return (Me.Scroll.Value.ToString)

        End Get

    End Property

End Structure