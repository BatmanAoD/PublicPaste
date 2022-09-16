# VERY VERY BAD UI choices

## Microsoft

* Excel - it is probably impossible for a casual user to guess what is going on
  sometimes
* Outlook
  * The _target_ of banner actions depends on _which banner_ is displayed.
    Specifically, selecting a message brings up the "message" banner, while
    selecting a task brings up the "Task List" banner. So it is easy to mark a
    task "complete" while trying to mark an email as "done" (i.e. mark-complete
    and archive the message).
  * When looking at an email you _sent_, the "reply" button *sends an email to
    yourself* rather than continuing the conversation thread.
  * *Any* response to a meeting invite *automatically deletes* the invite
    message. This does not appear to be customizable, and there does not appear
    to be any way to add a received event to the calendar without deleting the
    message.
  * Every mail folder records the location of the last-viewed item; when the
    folder is opened, the preview window and scroll-list start on that item.
    Viewing the most recent items appears to require *manually* scrolling to
    the top of the list.
* Remote Desktop - In the new connection window, when the cursor is placed
  after the IP address, pressing backspace *highlights* but *does not delete*
  the last character.
* Teams
  * Teams can initiate conversations with Skype users. However:
    * It will only do so if the user does *not* have a Teams account; there is
      no way to manually request that a message be sent to Skype, even if the
      user is currently active on Skype and has not logged in to Teams for a
      long time.
    * Skype users *cannot* initiate conversations with Teams users.
  * If a contact has *both* a Teams account *and* one or more numeric phone
    numbers, the only way to call the actual phone number using Teams VOIP is
    to *manually type* the number. Attempting to call the contact will *only*
    permit calling them via Teams-to-Teams VOIP.
* Visual Studio
  * When running tests, if there is a build failure, MSVS will ask if the user
    would like to use the _last successful build_ to run.
  * As part of its autocompletion logic, the editor sometimes deletes
    characters the user has typed. I haven't yet figured out what triggers
    this.

## Facebook (historical)

* The "like" button/icon indicated whether *anyone* had "liked" something, but
  had no way of indicating whether the *current user* had already "liked" it.
  The only way to tell whether you had "liked" something was to *click the
  button twice* and *check whether the counter incremented or decremented.*
