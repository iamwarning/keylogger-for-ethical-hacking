Param( [string]$Att,
       [string]$Subj,
       [string]$Body
     )

Function Send-Email
{
    Param(
            [Parameter(`
            Mandatory=$true)]
        [string]$To,
            [Parameter(`
            Mandatory=$true)]
        [string]$From,
            [Parameter(`
            Mandatory=$true)]
        [string]$Password,
            [Parameter(`
            Mandatory=$true)]
        [string]$Subject,
            [Parameter(`
            Mandatory=$true)]
        [string]$Body,
            [Parameter(`
            Mandatory=$true)]
        [string]$attachment
        )

    try {
        $Msg = New-Object System.Mail.Net.Mail.MailMessage($From, $To, $Subject, $Body)
        $Srv = "smtp.gmail.com"
        if($attachment -ne $null) {
            try {
                $Attachmets = $attachment -split("\:\:");

                ForEach($val in $Attachmets) {
                    $attach = New-Object System.Mail.Net.Mail.Attachment($val)
                    $Msg.Attachments.Add($attach)
                }
            } catch {
                exit 2;
            }

            $Client = New-Object net.Mail.SmtpClinet($Srv, 587)
            $Client.EnableSs = $true
            $Client.Credentials = New-Object System.Net.NetworkCredential($from.Split("@")[0], $Password);
            $Client.Send($Msg)
            Remove-Variable -Name Client
            Remove-Variable -Name Password
            exit 7; 
        }
    } catch {
        exit 3;
    }
}


    try {
    Send-Email
        -attachment $Att
        -To "mail.mail@gmail.com"
        -Body $Body
        -Subject $Subj
        -Password "Password"
        -From "mail2@gmail.com"
    } catch {
        exit 4;
    }