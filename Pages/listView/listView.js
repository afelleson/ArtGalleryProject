var commentList = [];
const baseUrl = 'C:\Users\4dyla\Programming\ArtGalleryProject\Pages\listView';

/* Set up events */
// $(document).ready(function() {
	// Add a click event for the filter button
	// document.querySelector("#filter-btn").addEventListener("click", (e) => {
		// var searchStr = 	document.querySelector("#search").value;
    	// findMatches(searchStr);
	// });

    // $(".dropdown-menu li a").click(function() {
        // var selection = $(this).text();
        // $(this).parents(".btn-group").find('.btn').html(selection + ' <span class="caret"></span>');
    // });

	// findMatches(" ");

// });

/* Search and display contact functions */

// Build output table from comma delimited list
function formatComments(json) {

    var result = '<table class="table table-success table-striped"><tr><th>Username</th><th>Body</th><th>Image Coords</th><th>Score</th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='name'>" + entry['name'] + "</td><td class='body'>" + entry['body'];
        result += "</td><td class='imgloc'>" + entry['imgloc'] + "</td><td class='score'>" + entry['score'] + "</td>";
        result += "<button type='button' class='btn btn-primary btn-sm' ";
		// FIX THIS
        result += "onclick=\"upvote(" + COMMENT + ")\">↑</button>";
        result += "<button type='button' class='btn btn-primary btn-sm' ";
		// FIX THIS
        result += "onclick=\"downvote(" + COMMENT + ")\">↓</button>";
    });
    result += "</table>";

    return result;
}

function displayMatches(results) {

    commentList = results["results"];
    console.log("Results:"+JSON.stringify(commentList));
    document.getElementById("searchresults").innerHTML = formatComments(commentList);
    
}

// function findMatches(search) {
	// only include / after find if search not empty
	// search = search.trim();
    // if (search != "") search = "/" + search;

	// console.log("Search:" + search);
    // fetch(baseUrl + '/contact/find' + search, {
            // method: 'get'
        // })
        // .then(response => response.json())
        // .then(json => displayMatches(json))
        // .catch(error => {
            // {
                // alert("Find Error: Something went wrong:" + error);
            // }
        // })
// }

/* Add contact functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
    document.getElementById("addfirst").value = "";
    document.getElementById("addlast").value = "";
    document.getElementById("addphone").value = "";

    findMatches(" ");

}

function sendComment() {
	// Temp Values
	x = 0
	y = 0
	zoom = 100
	
    console.log("Attempting to add an entry");
    console.log("Name:" + $('#addname').val());
    $('#searchresults').empty();
    fetch(baseUrl + '/comment/send/' + $('#addname').val() + "/" + $('#addbody').val() + "/" + '0' + "/" + x +"/" + y + "/" + zoom, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong:" + error);
            }
        })
}


function editContact(row) {
    console.log("start edit data: "+row+JSON.stringify(contactList[row]));

    console.log("First name of record: " + contactList[row]["first"] + " " + contactList[row]["last"]);
    editid = contactList[row]["ID"];

	document.getElementById("editfirst").value = contactList[row]["first"];
	document.getElementById("editlast").value = contactList[row]["last"];
	document.getElementById("editphone").value = contactList[row]["phone"];
	document.getElementById("edittype").innerText = contactList[row]["type"];
	
	//Save ID in modal
	var modal = document.querySelector("#editContact");
	modal.setAttribute("editid",editid);

}


function updateContact() {

	// Get ID in the modal
	var modal = document.querySelector("#editContact");
	id = modal.getAttribute("editid");
	
    console.log("Attempting to edit an entry:"+id); 

    fetch(baseUrl + '/contact/update/' + id + '/' + document.getElementById("editfirst").value 
    		+ '/' + document.getElementById("editlast").value + '/' + document.getElementById("editphone").value + '/' + document.getElementById("edittype").innerText, {
                method: 'get'
            })
        .then(alert("Record for " + document.getElementById("editfirst").value + ' ' + document.getElementById("editlast").value + " updated"))
        .catch(error => {
            {
                alert("Edit Error: something went wrong:" + error);
            }
        });
        
    findMatches(" ");

}


function deleteContact(id) {

    console.log("Attempting to delete an entry:" + id);
    fetch(baseUrl + '/contact/delete/' + id, {
            method: 'get'
        })
        .then(alert("Deleted Record: " + id))
        .catch(error => {
            {
                alert("Delete Error: Something went wrong:" + error);
            }
        });
     findMatches(" ");

}


