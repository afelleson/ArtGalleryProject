var commentList = [];
var baseUrl = 'http://18.218.64.106:5001';

var oldJson = "";
var mytoken = "";
var currentArtworkID = "8";

fetchRegularly=setInterval(fetchCommentsForArtwork,500);
fetchArtwork(currentArtworkID);
fetchArtList();

function changeArtwork(ID) {
    console.log("changeArtwork(" + ID + ") called")
    currentArtworkID = ID;
    fetchArtwork(ID);
}
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

document.getElementById('submit-comment').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addComment();
});

document.getElementById('submit-artwork').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addArtwork();
});


function displayArtInfo(results) {
    artDetails = results["result"];
    document.getElementById("artwork").src = decodeText(artDetails["path"]);
    var artworkInfo = decodeText(artDetails["title"]) + "<br>" + decodeText(artDetails["artist"]) + "<br>" + artDetails["year"];
    document.getElementById("artwork-info").innerHTML = artworkInfo;
}
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

function displayArtList(results) {
    artList = results["results"];
    document.getElementById("navbarSupportedContent").innerHTML += formatNavDropdown(artList);
}

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

// Build output table from comma delimited list
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

function completeVote(results){
    if (results["status"]=="success"){
        console.log("success in vote")
    };
}

function completeDelete(results){
    if (results["status"]=="success"){
        console.log("success in deletion")
    };
}

function completePin(results){
    if (results["status"]=="success"){
        console.log("success in pin")
    };
}

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


function toggleUpButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if green after click
        changeRating(commentID, "1");
      } else { // if gray after click
        changeRating(commentID, "-1");
      }
}


function resetVoteButton(buttonToActOn){
    // turn it gray
    console.log("attempting to reset button with id " + buttonToActOn.id)
    buttonToActOn.classList.remove('active');
}

function toggleDownButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if red after click
        changeRating(commentID, "-1");
      } else { // if gray after click
        changeRating(commentID, "1");
      }
}


function upvote(buttonPressed, commentID){
    console.log("upvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleUpButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("downvote-" + commentID));
}

function downvote(buttonPressed, commentID){
    console.log("downvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleDownButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("upvote-" + commentID));
}

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

function isJsonDifferent(newJson){
    if (JSON.stringify(oldJson)===JSON.stringify(newJson)){
        return false;
    } else {
        oldJson = newJson; // update saved json
        return true;
    }
}

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

function processAdd(results) {
    console.log("Add:", results["status"]);
    if (results["status"]=="success"){
        document.getElementById("addname").value = "";
        document.getElementById("addbody").value = "";
    } else {
        alert(results["status"]);
    }

}
function processAddArt(results) {
    console.log("Add:", results["status"]);
    if (results["status"]=="success"){
        document.getElementById("addtitle").value = "";
        document.getElementById("addartist").value = "";
        document.getElementById("addyear").value = "";
        document.getElementById("addpath").value = "";
    } else {
        alert(results["status"]);
    }
}
function processDelArt(results) {
    console.log("Delete:", results["status"]);
    if (results["status"]!="success"){
        alert(results["status"]);
    }
}

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

function encodeInput(inputText){
    var encodedText = encodeURIComponent(inputText)
    var encodedText = encodedText.replaceAll("%2F","%%");
    return encodedText;
}

function decodeText(text){
    var decodedText = text.replaceAll("%%", "%2F");
    var decodedText = decodeURIComponent(decodedText);
    return decodedText;
}

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

function staffInterfaceInvisible(){
    console.log("staffInterfaceInvisible() called");
    document.getElementById('login-button').style.display = 'block';
    
    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'none';
    }

}

function staffInterfaceVisible(){
    console.log("staffInterfaceVisible() called");
    document.getElementById('login-button').style.display = 'none';

    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'block';
    }


}


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

function processLogout(results){
    console.log("processLogout() called");
    if (results["status"]=="success"){
        console.log("logout successful")
        staffInterfaceInvisible();
    } else {
        alert(results["status"]);
    }
}

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

