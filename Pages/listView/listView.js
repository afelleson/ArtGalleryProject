var commentList = [];
var baseUrl = 'http://18.218.64.106:5001';

var oldJson = "";
var mytoken = "";
var currentArtworkID = "8";

fetchRegularly=setInterval(fetchCommentsForArtwork,500);
fetchArtwork(currentArtworkID);
fetchArtList();



/////////////////////
// EVENT LISTENERS //
/////////////////////

// Event listeners for submission buttons
document.getElementById('submit-comment').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addComment();
});

document.getElementById('submit-artwork').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addArtwork();
});

// Staff login event listeners
document.getElementById('login-go').addEventListener("click", loginStaff);

document.getElementById('StaffPW').addEventListener("keydown", (e)=> {
    if (e.code == "Enter") {
        event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
        console.log("Login enter detected");
        loginStaff();
    }
});

document.getElementById('logout-button').addEventListener("click", logoutStaff);

// Call functions on page exit
window.addEventListener('beforeunload', function (event) {
    logoutStaff();
    setTimeout(function(){ // close registration model after half a second
        console.log("waiting .5 sec");
    }, 500);
    clearInterval(fetchRegularly); // stop updating comment list

    // event.preventDefault() // these two lines cause a pop-up asking the user if they really want to close the tab
    // event.returnValue = '' // these two lines cause a pop-up asking the user if they really want to close the tab
  });

  
///////////////
// FUNCTIONS //
///////////////


/* General Functions */

// Encode text so it can be safely put in the database
function encodeInput(inputText){
    var encodedText = encodeURIComponent(inputText)
    var encodedText = encodeURIComponent(encodedText)
    // var encodedText = encodedText.replaceAll("%2F","%%");
    return encodedText;
}

// Decode text that has been encoded
function decodeText(text){
    // var decodedText = text.replaceAll("%%", "%2F");
    var decodedText = decodeURIComponent(text);
    var decodedText = decodeURIComponent(decodedText);
    return decodedText;
}


/* Artwork Functions */

//// Normal Functions ////

// Changes the page view, showing a new artwork
function changeArtwork(ID) {
    console.log("changeArtwork(" + ID + ") called")
    currentArtworkID = ID;
    fetchArtwork(ID);
}

// Formats Art list into html for dropdown
function formatNavDropdown(json) {

    var result = "<div class='dropdown'><button class='btn btn-secondary dropdown-toggle' type='button' data-bs-toggle='dropdown' aria-expanded='false'>";
    result +=  "Artwork";
    result += "</button><ul class='dropdown-menu'>";
    json.forEach(function(entry, i) {
        console.log(entry)
        result += "<li><button class='dropdown-item' onClick='changeArtwork(" + entry['ID'] + ")'>";
        result += entry['title'];
        result += "</button></li>";
    })

    result += "</ul></div>";

    return result;
}

// Displays Art list in dropdown
function displayArtList(results) {
    artList = results["results"];
    document.getElementById("navbarSupportedContent").innerHTML += formatNavDropdown(artList);
}

// Gets Art list
function fetchArtList() {
    fetch(baseUrl + '/artwork/getall', {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => displayArtList(json))
    .catch(error => {
        {
            alert("Fetch Art List Error: Something went wrong: \n" + error);
        }
    })
}

// Displays the current artwork's Title, Author, and Date published
function displayArtInfo(results) {
    artDetails = results["result"];
    document.getElementById("artwork").src = decodeText(artDetails["path"]);
    var artworkInfo = decodeText(artDetails["title"]) + "<br>" + decodeText(artDetails["artist"]) + "<br>" + artDetails["year"];
    document.getElementById("artwork-info").innerHTML = artworkInfo;
}

// Gets the info for a specific artwork, and displays the image for that artwork.
function fetchArtwork(artworkID) {
    fetch(baseUrl + '/artwork/getbyid/' + artworkID, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayArtInfo(json))
        .catch(error => {
            {
                alert("Fetch Art Error: Something went wrong: \n" + error);
            }
        })
}


//// Staff functions ////

// For adding artwork, clear fields and confirm success
function processAddArt(results) {
    console.log("Add:", results["status"]);
    if (results["status"]=="success"){
        document.getElementById("addtitle").value = "";
        document.getElementById("addartist").value = "";
        document.getElementById("addyear").value = "";
        document.getElementById("addpath").value = "";
        alert("Artwork added. Reload the page to see changes.")
    } else {
        alert(results["status"]);
    }
}

// Add new artwork to the database
function addArtwork() {
	
    console.log("Attempting to add artwork");
    console.log("Name:" + $('#addname').val());
    fetch(baseUrl + '/artwork/add/' + encodeInput($('#addtitle').val()) + "/" + encodeInput($('#addartist').val()) + "/" + $('#addyear').val() + "/" + encodeInput($('#addpath').val()) + "/" + mytoken, {
            method: 'get'
            // to do: put artwork id in the place of "0" above
        })
        .then(response => response.json())
        .then(json => processAddArt(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong: \n" + error);
            }
        })
}

// For deleting artwork, confirm success
function processDelArt(results) {
    console.log("Delete:", results["status"]);
    if (results["status"]=="success"){
        alert("Successful deletion. Reload page to see changes.");
    }
    else {
        alert(results["status"]);
    }
}

// Delete artwork from the database by id
function delArtwork(id) {
    fetch(baseUrl + '/artwork/delete/' + id + "/" + mytoken, {
        method: 'get'
        // to do: put artwork id in the place of "0" above
    })
    .then(response => response.json())
    .then(json => processDelArt(json))
    .catch(error => {
        {
            alert("Delete Error: Something went wrong: \n" + error);
        }
    })
}

/* Comment Functions */

//// Normal Functions ////

// Formats Comment list into html
function formatComments(json) {

    var result = '<table class="table"><tr><th>Username</th><th>Body</th><th>Rating</th><th> </th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='name'>" + decodeText(entry['name']) + "</td><td class='body'>" + decodeText(entry['commentText']);
        result += "</td><td class='rating'>";
        result += entry['rating'];
        // upvote button
        result += "<button type='button' id='upvote-" + entry['ID'] + "' class='btn btn-upvote btn-sm' data-bs-toggle='button' aria-pressed='false' ";
        result += "onclick=\"upvote(this," + entry['ID'] + ")\">↑</button>";
        // downvote button
        result += "<button type='button' id='downvote-" + entry['ID'] + "' class='btn btn-downvote btn-sm' data-bs-toggle='button' aria-pressed='false' ";
        result += "onclick=\"downvote(this," + entry['ID'] + ")\">↓</button>";
        // delete comment button
        result += "<button type='button' id='delete-" + entry['ID'] +"'class='btn staff-stuff btn-danger btn-sm' "
        result += "onclick='deleteComment(" + entry['ID'] + ")'>Delete</button>" 
        // pin comment button
        var pinColor = "warning";
        var pinAct = "Pin"
        if (entry['isPinned'] == "1") {
            var pinColor = "secondary";
            var pinAct = "Unpin"
        }
        result += "<button type='button' id='pin-" + entry['ID'] + "' class='btn staff-stuff btn-" + pinColor + " btn-sm' ";
        result += "onclick=\"pinComment(" + entry['ID'] + ")\">" + pinAct + "</button></td>";
        // pinned icon
        result += "<td> ";
        if (entry['isPinned'] == "1") {
            result += "<img src='solid-tack.svg' class='pin-icon'/>";
        }
        result += "</td>";
    });
    result += "</table>";

    return result;
}

// Displays Comment list
function displayComments(isJsonDiff, results) {
    if (isJsonDiff){
        commentList = results["results"];
        console.log("remaking table of comments");
        document.getElementById("searchresults").innerHTML = formatComments(commentList);
        if (mytoken!=""){ // more secure way would be to do an API call to see if mytoken is in the database
            staffInterfaceVisible();
        }
    }
}

// Checks if any comment info in the database has changed
function isJsonDifferent(newJson){
    if (JSON.stringify(oldJson)===JSON.stringify(newJson)){
        return false;
    } else {
        oldJson = newJson; // update saved json
        return true;
    }
}

// Checks what comment sorting method is currently selected
function getSortMethod() {
    const sortMethods = document.querySelectorAll('input[name="sortbtns"]');
    var resultMethod = null;
    sortMethods.forEach((button) => {
        if (button.checked) {
            resultMethod = button.value;
        }
    });
    return resultMethod
}

// Gets Comment list for the current artwork
function fetchCommentsForArtwork() {
	// Temp Values
    var sortParam;
    sortParam = getSortMethod();
	
    fetch(baseUrl + '/comment/fetchforwork/' + currentArtworkID + "/" + sortParam, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayComments(isJsonDifferent(json),json))
        .catch(error => {
            {
                alert("Fetch Comment Error: Something went wrong: \n" + error);
            }
        })
}



// For adding comments, clear fields and confirm success
function processAdd(results) {
    console.log("Add:", results["status"]);
    if (results["status"]=="success"){
        document.getElementById("addname").value = "";
        document.getElementById("addbody").value = "";
    } else {
        alert(results["status"]);
    }

}

// Adds comment to database
function addComment() {
	// Temp Values
	x = "1"
	y = "1"
	width = "100"
	
    console.log("Attempting to add an entry");
    console.log("Name:" + $('#addname').val());
    fetch(baseUrl + '/comment/add/' + encodeInput($('#addname').val()) + "/" + encodeInput($('#addbody').val()) + "/" + currentArtworkID + "/" + x +"/" + y + "/" + width, {
            method: 'get'
            // to do: put artwork id in the place of "0" above
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong: \n" + error);
            }
        })
}




// Check for success in voting
function completeVote(results){
    if (results["status"]=="success"){
        console.log("success in vote")
    };
}

// Vote on specific comment by 1 or -1
function changeRating(commentID, vote){
    fetch(baseUrl + '/comment/changerating/' + commentID + "/" + vote, {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => completeVote(json))
    .catch(error => {
        {
            alert("Vote Error: Something went wrong: \n" + error);
        }
    })
}

// Resets specific vote toggle to "inactive"
function resetVoteButton(buttonToActOn){
    // turn it gray
    console.log("attempting to reset button with id " + buttonToActOn.id)
    buttonToActOn.classList.remove('active');
}

// Defines upvote as vote +1
function toggleUpButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if green after click
        changeRating(commentID, "1");
      } else { // if gray after click
        changeRating(commentID, "-1");
      }
}

// Upvotes comment, undoes downvote if there is one
function upvote(buttonPressed, commentID){
    console.log("upvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleUpButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("downvote-" + commentID));
}

// Defines downvote as vote -1
function toggleDownButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if red after click
        changeRating(commentID, "-1");
      } else { // if gray after click
        changeRating(commentID, "1");
      }
}

// Downvotes comment, undoes upvote if there is one
function downvote(buttonPressed, commentID){
    console.log("downvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleDownButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("upvote-" + commentID));
}

// Note: Upvote and downvote toggles only hold their state for half a second before the whole comments table is reloaded.
// In the future, it would be nice to not remake those buttons when the rest of the table remakes itself, 
// and have them reset after 20 seconds or so (for the next user, if this is on an iPad on the wall in the gallery)








//// Staff functions ////

// Check for success in deleting comment
function completeDelete(results){
    if (results["status"]=="success"){
        console.log("success in deletion")
    };
}

// Delete comment
function deleteComment(commentID) {
    fetch(baseUrl + '/comment/delete/' + commentID + "/" + mytoken, {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => completeDelete(json))
    .catch(error => {
        {
            alert("Deletion Error: Something went wrong: \n" + error);
        }
    })
}

// Check for success in pinning comment
function completePin(results){
    if (results["status"]=="success"){
        console.log("success in pin")
    };
}

// Toggles pin state for specific comment
function pinComment(commentID) {
    fetch(baseUrl + '/comment/togglepin/' + commentID + "/" + mytoken, {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => completePin(json))
    .catch(error => {
        {
            alert("Pin Error: Something went wrong: \n" + error);
        }
    })
}

/* Staff interface functions */

// Make staff interface invisible
function staffInterfaceInvisible(){
    console.log("staffInterfaceInvisible() called");
    document.getElementById('login-button').style.display = 'block';
    
    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'none';
    }

}

// Make staff interface visible
function staffInterfaceVisible(){
    console.log("staffInterfaceVisible() called");
    document.getElementById('login-button').style.display = 'none';

    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'block';
    }


}

// Close login modal, apply staff token, unhide staff UI, check success
function processLogin(results){
    if (results["status"]=="success"){
        // close login modal
        const clickEvent = new MouseEvent('click');
        document.getElementById('login-close').dispatchEvent(clickEvent);

        mytoken = results['token'];

        console.log("login successful")

        staffInterfaceVisible();
    } else {
        alert(results["status"]);
    }
}

// Login as staff. Backend generates a token and adds it to the database.
function loginStaff(){
    console.log("loginStaff() called");
    fetch(baseUrl + '/stafflogin/' + $('#StaffPW').val(), {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => processLogin(json))
    .catch(error => {
        {
            alert("Login Error: Something went wrong in loginStaff(): " + error);
        }
    })
}

// Check logout success, hide staff UI
function processLogout(results){
    console.log("processLogout() called");
    if (results["status"]=="success"){
        console.log("logout successful")
        staffInterfaceInvisible();
    } else {
        alert(results["status"]);
    }
}

// Logout staff, delete the session's token from the database
function logoutStaff(){
    console.log("logoutStaff() called with token " + mytoken);
    fetch(baseUrl + '/stafflogout/' + mytoken, {
        method: 'get',
        keepalive: true // so the API call completes even when called on page unload. Not working as expected right now.
    })
    .then(response => response.json())
    .then(json => processLogout(json))
    .catch(error => {
        {
            alert("Logout Error: Something went wrong in logoutStaff(): " + error);
        }
    })
    mytoken = "";
    staffInterfaceInvisible();
}

